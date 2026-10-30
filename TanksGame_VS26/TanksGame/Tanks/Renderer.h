#pragma once

#include <array>
#include <map>
#include <string>
#include <utility>
#include "ISingleton.h"
#include "Direction.h"

namespace Gdiplus
{
	class Bitmap;
	class Graphics;
}

// Window + GDI+ renderer. All the coordinates are in logical pixels (scaled up to the window)
class CRenderer : public ISingleton<CRenderer>
{
public:
	static const int s_iTankSkins = 3;
	static const int s_iTankSpriteFrames = 2;
	static const int s_iTankSpriteSize = 14;
	static const int s_iExplosionFrames = 3;
	static const int s_iExplosionSpriteSize = 16;
	static const int s_iCannonSpriteWidth = 6;
	static const int s_iCannonSpriteHeight = 10;

	~CRenderer();

	// Create the window (size in logical pixels) and load the sprites
	bool Init(const wchar_t* _sTitle, int _iWidth, int _iHeight);
	// Process the window messages, returns false when the window has been closed
	bool ProcessMessages();

	void BeginFrame(unsigned int _uColor);
	void EndFrame();
	// Offset added to all the draw calls (logical pixels)
	void SetOrigin(int _iX, int _iY);

	// Colors are ARGB (0xAARRGGBB)
	void DrawRect(int _iX, int _iY, int _iWidth, int _iHeight, unsigned int _uColor);
	void DrawTank(int _iSkin, int _iColor, EDirection _eDirection, int _iFrame, int _iCenterX, int _iCenterY);
	void DrawExplosion(int _iColor, int _iFrame, int _iCenterX, int _iCenterY);
	void DrawCannon(int _iColor, EDirection _eDirection, int _iCenterX, int _iCenterY);
	void RenderText(int _iX, int _iY, const std::string& _sText, unsigned int _uColor, int _iSize, bool _bCentered = false);

	// Color indices used for the dead tanks and for the cannons
	static const int s_iDeadColor = 16;
	static const int s_iCannonColor = 17;
	// Color index to draw a solid white silhouette (hit flash)
	static const int s_iFlashColor = 18;

	// Tank color index (0-15) to ARGB
	static unsigned int GetPaletteColor(int _iColor);

private:
	struct STankSprites
	{
		Gdiplus::Bitmap* aFrames[s_iTankSpriteFrames][static_cast<int>(EDirection::Count)] = {};
	};
	typedef std::array<Gdiplus::Bitmap*, s_iExplosionFrames> TExplosionSprites;
	typedef std::array<Gdiplus::Bitmap*, static_cast<int>(EDirection::Count)> TCannonSprites;

	bool LoadSprites();
	const STankSprites& GetTankSprites(int _iSkin, int _iColor);
	const TExplosionSprites& GetExplosionSprites(int _iColor);
	const TCannonSprites& GetCannonSprites(int _iColor);
	void DrawBitmap(Gdiplus::Bitmap* _pBitmap, int _iX, int _iY);

private:
	bool m_bInitialized = false;
	int m_iWidth = 0;
	int m_iHeight = 0;
	int m_iScale = 1;
	int m_iOriginX = 0;
	int m_iOriginY = 0;

	void* m_hWnd = nullptr;
	void* m_hBackBufferDC = nullptr;
	void* m_hBackBufferBitmap = nullptr;
	void* m_hOldBitmap = nullptr;
	unsigned long long m_uGdiplusToken = 0;
	Gdiplus::Graphics* m_pGraphics = nullptr;

	Gdiplus::Bitmap* m_pTanksSheet = nullptr;
	Gdiplus::Bitmap* m_pExplosionSheet = nullptr;
	Gdiplus::Bitmap* m_pCannonSheet = nullptr;
	// Tinted and rotated sprites (key: skin, color)
	std::map<std::pair<int, int>, STankSprites> m_tTankSprites;
	// Tinted explosion sprites (key: color)
	std::map<int, TExplosionSprites> m_tExplosionSprites;
	// Tinted and rotated cannon sprites (key: color)
	std::map<int, TCannonSprites> m_tCannonSprites;
};
