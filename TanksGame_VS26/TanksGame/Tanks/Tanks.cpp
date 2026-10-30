#include <chrono>
#include <thread>

#include "TanksManager.h"
#include "Renderer.h"
#include "Tanks/PlayerTank.h"
#include "Tanks/RandTank.h"
#include "Tanks/MakuTank.h"

#pragma execution_character_set( "utf-8" )

struct STankPos
{
	STankPos(int _iX, int _iY, int _iColor)
		: iX(_iX)
		, iY(_iY)
		, iColor(_iColor)
	{}
	int iX;
	int iY;
	int iColor;

	template <typename T>
	T* CreateTank()
	{
		return new T(iX, iY, iColor);
	}
};

static void CreateTanks()
{
	const CMap& rMap = CTanksManager::GetInstance().GetMap();
	const int iMapWidth = rMap.GetWidth();
	const int iMapHeight = rMap.GetHeight();

	STankPos aTankPos[] =
	{
		STankPos(iMapWidth / 4, iMapHeight / 4, 1),
		STankPos(3 * iMapWidth / 4, 3 * iMapHeight / 4, 2),
		STankPos(3 * iMapWidth / 4, iMapHeight / 4, 3),
		STankPos(iMapWidth / 4, 3 * iMapHeight / 4, 4),
		STankPos(iMapWidth / 2, iMapHeight / 4, 5),
		STankPos(3 * iMapWidth / 4, iMapHeight / 2, 6),
		STankPos(iMapWidth / 4, iMapHeight / 2, 7),
		STankPos(iMapWidth / 2, 3 * iMapHeight / 4, 14),
		STankPos(iMapWidth / 8, iMapHeight / 8, 9),
		STankPos(7 * iMapWidth / 8, 7 * iMapHeight / 8, 10),
		STankPos(7 * iMapWidth / 8, iMapHeight / 8, 11),
		STankPos(iMapWidth / 8, 7 * iMapHeight / 8, 12),
		STankPos(iMapWidth / 2, iMapHeight / 2, 13),
		STankPos(7 * iMapWidth / 8, iMapHeight / 2, 15),
		STankPos(iMapWidth / 8, iMapHeight / 2, 0),
		STankPos(iMapWidth / 2, 7 * iMapHeight / 8, 8),
	};
	static_assert(sizeof(aTankPos) / sizeof(aTankPos[0]) == CTanksManager::s_iMaxTanks);

	// Añadir los tanques aqui!
	unsigned int uIndex(0u);
	CTanksManager::GetInstance().AddTank(aTankPos[uIndex++].CreateTank<MakuTank>());
	CTanksManager::GetInstance().AddTank(aTankPos[uIndex++].CreateTank<MakuTank>());                                                                                
}


int main()
{
	CTanksManager::CreateSingleton();

	CreateTanks();

	if (CRenderer::GetInstance().Init(L"Tanks", CTanksManager::GetInstance().GetWindowWidth(), CTanksManager::GetInstance().GetWindowHeight()))
	{
		const std::chrono::microseconds oTickDuration(1000000 / CTanksManager::s_iTicksPerSecond);
		auto oNextTick = std::chrono::steady_clock::now();

		while (CRenderer::GetInstance().ProcessMessages())
		{
			CTanksManager::GetInstance().Update();
			CTanksManager::GetInstance().Render();

			oNextTick += oTickDuration;
			const auto oNow = std::chrono::steady_clock::now();
			if (oNextTick < oNow)
			{
				oNextTick = oNow;
			}
			std::this_thread::sleep_until(oNextTick);
		}
	}

	CTanksManager::DestroySingleton();
	CRenderer::DestroySingleton();
}
