#include "Renderer.h"

#define NOMINMAX
#include <windows.h>
#include <algorithm>
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>
#include <filesystem>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")

namespace
{
	const wchar_t* s_sWindowClass = L"TanksWindow";

	// tanks.png: cells of 14x13 in 4 columns, 2 frames per tank (skin)
	const int s_iTankCellWidth = 14;
	const int s_iTankCellHeight = 13;
	const int s_iTankSheetColumns = 4;

	// tank_explosion.png: cells of 16x16 (frames in order)
	const int s_aExplosionCells[CRenderer::s_iExplosionFrames][2] =
	{
		{ 0, 16 },
		{ 16, 0 },
		{ 0, 0 },
	};

	// Sprites are drawn looking up
	const Gdiplus::RotateFlipType s_aRotations[] =
	{
		Gdiplus::RotateNoneFlipNone, // Up
		Gdiplus::Rotate180FlipNone, // Down
		Gdiplus::Rotate270FlipNone, // Left
		Gdiplus::Rotate90FlipNone, // Right
	};
	static_assert(sizeof(s_aRotations) / sizeof(s_aRotations[0]) == static_cast<size_t>(EDirection::Count));

	bool s_bWindowOpen = false;

	LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_uMsg)
		{
		case WM_KEYDOWN:
			if (_wParam == VK_ESCAPE)
			{
				DestroyWindow(_hWnd);
				return 0;
			}
			break;
		case WM_ERASEBKGND:
			return 1;
		case WM_DESTROY:
			s_bWindowOpen = false;
			return 0;
		}
		return DefWindowProcW(_hWnd, _uMsg, _wParam, _lParam);
	}

	// Look for the Resources folder going up from the executable folder
	std::filesystem::path FindResourcesPath()
	{
		wchar_t sExePath[MAX_PATH] = {};
		GetModuleFileNameW(nullptr, sExePath, MAX_PATH);
		std::filesystem::path oDir = std::filesystem::path(sExePath).parent_path();
		for (int i = 0; i < 6 && !oDir.empty(); ++i)
		{
			const std::filesystem::path oResources = oDir / L"Resources";
			if (std::filesystem::exists(oResources / L"tanks.png"))
			{
				return oResources;
			}
			if (oDir == oDir.parent_path())
			{
				break;
			}
			oDir = oDir.parent_path();
		}
		return L"../Resources";
	}

	// Copy a cell of the sheet to a new sprite (padded with transparent pixels up to the sprite size), multiplying the (gray scale) pixels by the tint color.
	// With the flash color all the visible pixels are painted white
	Gdiplus::Bitmap* CreateTintedSprite(Gdiplus::Bitmap* _pSheet, int _iX, int _iY, int _iWidth, int _iHeight, int _iSpriteWidth, int _iSpriteHeight, int _iColor)
	{
		const bool bSilhouette = _iColor == CRenderer::s_iFlashColor;
		const unsigned int _uTint = CRenderer::GetPaletteColor(_iColor);
		const Gdiplus::Color oTint(_uTint);
		Gdiplus::Bitmap* pSprite = new Gdiplus::Bitmap(_iSpriteWidth, _iSpriteHeight, PixelFormat32bppARGB);
		for (int iY = 0; iY < _iSpriteHeight; ++iY)
		{
			for (int iX = 0; iX < _iSpriteWidth; ++iX)
			{
				Gdiplus::Color oColor(0, 0, 0, 0);
				if (iX < _iWidth && iY < _iHeight)
				{
					Gdiplus::Color oPixel;
					_pSheet->GetPixel(_iX + iX, _iY + iY, &oPixel);
					oColor = bSilhouette ? Gdiplus::Color(oPixel.GetA(), 255, 255, 255) : Gdiplus::Color(oPixel.GetA(),
						static_cast<BYTE>(oPixel.GetR() * oTint.GetR() / 255),
						static_cast<BYTE>(oPixel.GetG() * oTint.GetG() / 255),
						static_cast<BYTE>(oPixel.GetB() * oTint.GetB() / 255));
				}
				pSprite->SetPixel(iX, iY, oColor);
			}
		}
		return pSprite;
	}
}

CRenderer::~CRenderer()
{
	for (auto& rPair : m_tTankSprites)
	{
		for (auto& rFrame : rPair.second.aFrames)
		{
			for (Gdiplus::Bitmap* pBitmap : rFrame)
			{
				delete pBitmap;
			}
		}
	}
	for (auto& rPair : m_tExplosionSprites)
	{
		for (Gdiplus::Bitmap* pBitmap : rPair.second)
		{
			delete pBitmap;
		}
	}
	for (auto& rPair : m_tCannonSprites)
	{
		for (Gdiplus::Bitmap* pBitmap : rPair.second)
		{
			delete pBitmap;
		}
	}
	delete m_pTanksSheet;
	delete m_pExplosionSheet;
	delete m_pCannonSheet;
	delete m_pGraphics;

	if (m_hBackBufferDC)
	{
		SelectObject(static_cast<HDC>(m_hBackBufferDC), static_cast<HGDIOBJ>(m_hOldBitmap));
		DeleteObject(static_cast<HGDIOBJ>(m_hBackBufferBitmap));
		DeleteDC(static_cast<HDC>(m_hBackBufferDC));
	}
	if (m_hWnd && s_bWindowOpen)
	{
		DestroyWindow(static_cast<HWND>(m_hWnd));
	}
	if (m_uGdiplusToken)
	{
		Gdiplus::GdiplusShutdown(static_cast<ULONG_PTR>(m_uGdiplusToken));
	}
	if (m_bInitialized)
	{
		timeEndPeriod(1);
	}
}

bool CRenderer::Init(const wchar_t* _sTitle, int _iWidth, int _iHeight)
{
	SetProcessDPIAware();
	// Precise Sleep for the game loop
	timeBeginPeriod(1);
	m_bInitialized = true;

	Gdiplus::GdiplusStartupInput oStartupInput;
	ULONG_PTR uToken = 0;
	if (Gdiplus::GdiplusStartup(&uToken, &oStartupInput, nullptr) != Gdiplus::Ok)
	{
		return false;
	}
	m_uGdiplusToken = uToken;

	if (!LoadSprites())
	{
		MessageBoxW(nullptr, L"Can't load the sprites (tanks.png, tank_explosion.png, cannon.png) from the Resources folder", _sTitle, MB_ICONERROR);
		return false;
	}

	// Biggest integer scale that fits in the screen
	RECT oWorkArea;
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &oWorkArea, 0);
	const int iScreenWidth = oWorkArea.right - oWorkArea.left;
	const int iScreenHeight = oWorkArea.bottom - oWorkArea.top;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;
	m_iScale = std::max(1, std::min((iScreenWidth - 64) / _iWidth, (iScreenHeight - 64) / _iHeight));

	WNDCLASSEXW oWindowClass = {};
	oWindowClass.cbSize = sizeof(WNDCLASSEXW);
	oWindowClass.lpfnWndProc = WndProc;
	oWindowClass.hInstance = GetModuleHandleW(nullptr);
	oWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	oWindowClass.lpszClassName = s_sWindowClass;
	RegisterClassExW(&oWindowClass);

	const DWORD uStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT oRect = { 0, 0, m_iWidth * m_iScale, m_iHeight * m_iScale };
	AdjustWindowRect(&oRect, uStyle, FALSE);
	const int iWindowWidth = oRect.right - oRect.left;
	const int iWindowHeight = oRect.bottom - oRect.top;

	HWND hWnd = CreateWindowExW(0, s_sWindowClass, _sTitle, uStyle,
		oWorkArea.left + (iScreenWidth - iWindowWidth) / 2, oWorkArea.top + (iScreenHeight - iWindowHeight) / 2,
		iWindowWidth, iWindowHeight, nullptr, nullptr, oWindowClass.hInstance, nullptr);
	if (!hWnd)
	{
		return false;
	}
	m_hWnd = hWnd;
	s_bWindowOpen = true;

	// Back buffer
	HDC hDC = GetDC(hWnd);
	HDC hBackBufferDC = CreateCompatibleDC(hDC);
	HBITMAP hBackBufferBitmap = CreateCompatibleBitmap(hDC, m_iWidth * m_iScale, m_iHeight * m_iScale);
	m_hOldBitmap = SelectObject(hBackBufferDC, hBackBufferBitmap);
	m_hBackBufferDC = hBackBufferDC;
	m_hBackBufferBitmap = hBackBufferBitmap;
	ReleaseDC(hWnd, hDC);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	return true;
}

bool CRenderer::ProcessMessages()
{
	MSG oMsg;
	while (PeekMessageW(&oMsg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&oMsg);
		DispatchMessageW(&oMsg);
	}
	return s_bWindowOpen;
}

void CRenderer::BeginFrame(unsigned int _uColor)
{
	if (!s_bWindowOpen)
	{
		return;
	}
	delete m_pGraphics;
	m_pGraphics = new Gdiplus::Graphics(static_cast<HDC>(m_hBackBufferDC));
	m_pGraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	m_pGraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
	m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
	m_pGraphics->Clear(Gdiplus::Color(_uColor));
}

void CRenderer::EndFrame()
{
	if (!m_pGraphics)
	{
		return;
	}
	delete m_pGraphics;
	m_pGraphics = nullptr;

	if (s_bWindowOpen)
	{
		HWND hWnd = static_cast<HWND>(m_hWnd);
		HDC hDC = GetDC(hWnd);
		BitBlt(hDC, 0, 0, m_iWidth * m_iScale, m_iHeight * m_iScale, static_cast<HDC>(m_hBackBufferDC), 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hDC);
	}
}

void CRenderer::SetOrigin(int _iX, int _iY)
{
	m_iOriginX = _iX;
	m_iOriginY = _iY;
}

void CRenderer::DrawRect(int _iX, int _iY, int _iWidth, int _iHeight, unsigned int _uColor)
{
	if (!m_pGraphics)
	{
		return;
	}
	Gdiplus::SolidBrush oBrush((Gdiplus::Color(_uColor)));
	m_pGraphics->FillRectangle(&oBrush, (_iX + m_iOriginX) * m_iScale, (_iY + m_iOriginY) * m_iScale, _iWidth * m_iScale, _iHeight * m_iScale);
}

void CRenderer::DrawTank(int _iSkin, int _iColor, EDirection _eDirection, int _iFrame, int _iCenterX, int _iCenterY)
{
	const STankSprites& rSprites = GetTankSprites(_iSkin, _iColor);
	const int iHalfSize = s_iTankSpriteSize / 2;
	DrawBitmap(rSprites.aFrames[_iFrame % s_iTankSpriteFrames][static_cast<int>(_eDirection)], _iCenterX - iHalfSize, _iCenterY - iHalfSize);
}

void CRenderer::DrawExplosion(int _iColor, int _iFrame, int _iCenterX, int _iCenterY)
{
	const TExplosionSprites& rSprites = GetExplosionSprites(_iColor);
	const int iHalfSize = s_iExplosionSpriteSize / 2;
	DrawBitmap(rSprites[std::clamp(_iFrame, 0, s_iExplosionFrames - 1)], _iCenterX - iHalfSize, _iCenterY - iHalfSize);
}

void CRenderer::DrawCannon(int _iColor, EDirection _eDirection, int _iCenterX, int _iCenterY)
{
	Gdiplus::Bitmap* pSprite = GetCannonSprites(_iColor)[static_cast<int>(_eDirection)];
	DrawBitmap(pSprite, _iCenterX - static_cast<int>(pSprite->GetWidth()) / 2, _iCenterY - static_cast<int>(pSprite->GetHeight()) / 2);
}

void CRenderer::RenderText(int _iX, int _iY, const std::string& _sText, unsigned int _uColor, int _iSize, bool _bCentered)
{
	if (!m_pGraphics || _sText.empty())
	{
		return;
	}
	// UTF-8 to UTF-16
	const int iLength = MultiByteToWideChar(CP_UTF8, 0, _sText.c_str(), static_cast<int>(_sText.size()), nullptr, 0);
	std::wstring sText(iLength, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, _sText.c_str(), static_cast<int>(_sText.size()), &sText[0], iLength);

	Gdiplus::Font oFont(L"Consolas", static_cast<Gdiplus::REAL>(_iSize * m_iScale), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush oBrush((Gdiplus::Color(_uColor)));
	Gdiplus::StringFormat oFormat;
	if (_bCentered)
	{
		oFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	}
	const Gdiplus::PointF oPosition(static_cast<Gdiplus::REAL>((_iX + m_iOriginX) * m_iScale), static_cast<Gdiplus::REAL>((_iY + m_iOriginY) * m_iScale));
	m_pGraphics->DrawString(sText.c_str(), static_cast<INT>(sText.size()), &oFont, oPosition, &oFormat, &oBrush);
}

unsigned int CRenderer::GetPaletteColor(int _iColor)
{
	static const unsigned int s_aPalette[] =
	{
		0xFFB0703A, // 0 Brown
		0xFF4A7DFF, // 1 Blue
		0xFF3FCF5A, // 2 Green
		0xFF3FD0D0, // 3 Cyan
		0xFFE84545, // 4 Red
		0xFFCC55DD, // 5 Magenta
		0xFFE8A33A, // 6 Dark yellow
		0xFFD0D0D0, // 7 Light gray
		0xFFA8C83A, // 8 Olive
		0xFF7FA8FF, // 9 Light blue
		0xFF8CF08C, // 10 Light green
		0xFF8CF5F5, // 11 Light cyan
		0xFFFF7A7A, // 12 Light red
		0xFFF58CF5, // 13 Light magenta
		0xFFFFE85A, // 14 Yellow
		0xFFFFFFFF, // 15 White
	};
	if (_iColor == s_iDeadColor)
	{
		return 0xFF5A5E66;
	}
	if (_iColor == s_iCannonColor)
	{
		return 0xFFFF5A3C;
	}
	if (_iColor == s_iFlashColor)
	{
		return 0xFFFFFFFF;
	}
	return s_aPalette[_iColor & 15];
}

bool CRenderer::LoadSprites()
{
	const std::filesystem::path oResourcesPath = FindResourcesPath();
	m_pTanksSheet = Gdiplus::Bitmap::FromFile((oResourcesPath / L"tanks.png").c_str());
	m_pExplosionSheet = Gdiplus::Bitmap::FromFile((oResourcesPath / L"tank_explosion.png").c_str());
	m_pCannonSheet = Gdiplus::Bitmap::FromFile((oResourcesPath / L"cannon.png").c_str());
	return m_pTanksSheet && m_pTanksSheet->GetLastStatus() == Gdiplus::Ok
		&& m_pExplosionSheet && m_pExplosionSheet->GetLastStatus() == Gdiplus::Ok
		&& m_pCannonSheet && m_pCannonSheet->GetLastStatus() == Gdiplus::Ok;
}

const CRenderer::STankSprites& CRenderer::GetTankSprites(int _iSkin, int _iColor)
{
	_iSkin = ((_iSkin % s_iTankSkins) + s_iTankSkins) % s_iTankSkins;
	const std::pair<int, int> oKey(_iSkin, _iColor);
	auto it = m_tTankSprites.find(oKey);
	if (it != m_tTankSprites.end())
	{
		return it->second;
	}

	STankSprites& rSprites = m_tTankSprites[oKey];
	for (int iFrame = 0; iFrame < s_iTankSpriteFrames; ++iFrame)
	{
		const int iCell = _iSkin * s_iTankSpriteFrames + iFrame;
		const int iX = (iCell % s_iTankSheetColumns) * s_iTankCellWidth;
		const int iY = (iCell / s_iTankSheetColumns) * s_iTankCellHeight;
		Gdiplus::Bitmap* pUpSprite = CreateTintedSprite(m_pTanksSheet, iX, iY, s_iTankCellWidth, s_iTankCellHeight, s_iTankSpriteSize, s_iTankSpriteSize, _iColor);
		for (int iDirection = 0; iDirection < static_cast<int>(EDirection::Count); ++iDirection)
		{
			Gdiplus::Bitmap* pSprite = pUpSprite->Clone(0, 0, s_iTankSpriteSize, s_iTankSpriteSize, PixelFormat32bppARGB);
			pSprite->RotateFlip(s_aRotations[iDirection]);
			rSprites.aFrames[iFrame][iDirection] = pSprite;
		}
		delete pUpSprite;
	}
	return rSprites;
}

const CRenderer::TExplosionSprites& CRenderer::GetExplosionSprites(int _iColor)
{
	auto it = m_tExplosionSprites.find(_iColor);
	if (it != m_tExplosionSprites.end())
	{
		return it->second;
	}

	TExplosionSprites& rSprites = m_tExplosionSprites[_iColor];
	for (int iFrame = 0; iFrame < s_iExplosionFrames; ++iFrame)
	{
		rSprites[iFrame] = CreateTintedSprite(m_pExplosionSheet, s_aExplosionCells[iFrame][0], s_aExplosionCells[iFrame][1],
			s_iExplosionSpriteSize, s_iExplosionSpriteSize, s_iExplosionSpriteSize, s_iExplosionSpriteSize, _iColor);
	}
	return rSprites;
}

const CRenderer::TCannonSprites& CRenderer::GetCannonSprites(int _iColor)
{
	auto it = m_tCannonSprites.find(_iColor);
	if (it != m_tCannonSprites.end())
	{
		return it->second;
	}

	TCannonSprites& rSprites = m_tCannonSprites[_iColor];
	Gdiplus::Bitmap* pUpSprite = CreateTintedSprite(m_pCannonSheet, 0, 0, s_iCannonSpriteWidth, s_iCannonSpriteHeight,
		s_iCannonSpriteWidth, s_iCannonSpriteHeight, _iColor);
	for (int iDirection = 0; iDirection < static_cast<int>(EDirection::Count); ++iDirection)
	{
		Gdiplus::Bitmap* pSprite = pUpSprite->Clone(0, 0, s_iCannonSpriteWidth, s_iCannonSpriteHeight, PixelFormat32bppARGB);
		pSprite->RotateFlip(s_aRotations[iDirection]);
		rSprites[iDirection] = pSprite;
	}
	delete pUpSprite;
	return rSprites;
}

void CRenderer::DrawBitmap(Gdiplus::Bitmap* _pBitmap, int _iX, int _iY)
{
	if (!m_pGraphics || !_pBitmap)
	{
		return;
	}
	const int iWidth = static_cast<int>(_pBitmap->GetWidth());
	const int iHeight = static_cast<int>(_pBitmap->GetHeight());
	const Gdiplus::Rect oDestination((_iX + m_iOriginX) * m_iScale, (_iY + m_iOriginY) * m_iScale, iWidth * m_iScale, iHeight * m_iScale);
	m_pGraphics->DrawImage(_pBitmap, oDestination, 0, 0, iWidth, iHeight, Gdiplus::UnitPixel);
}
