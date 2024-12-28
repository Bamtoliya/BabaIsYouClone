#include "pch.h"
#include "CMainGame.h"
#include "Designs.h"

CMainGame::CMainGame()
	: m_hDC(GetDC(g_hWnd)), m_ullTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

void CMainGame::Initialize()
{
	cout << "CMainGame Initialized\n";
	CSceneManager::GetInstance()->SetScene(SCENEID::Edit);
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"BABA.png", L"BABA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"KEKE.png", L"KEKE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"BOX.png", L"BOX");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CIRCLE.png", L"CIRCLE");	
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CURSOR.png", L"CURSOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"DOOR.png", L"DOOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"DUST.png", L"DUST");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"FLAG.png", L"FLAG");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"FLOWER.png", L"FLOWER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"KEY.png", L"KEY");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LOVE.png", L"LOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"ROCK.png", L"ROCK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"STAR.png", L"STAR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_AND.png", L"Text_AND");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_DEFEAT.png", L"Text_DEFEAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_END.png", L"Text_END");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_FLOAT.png", L"Text_FLOAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_HOT.png", L"Text_HOT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_IS.png", L"Text_IS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_MELT.png", L"Text_MELT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_MOVE.png", L"Text_MOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_OPEN.png", L"Text_OPEN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_PULL.png", L"Text_PULL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_PUSH.png", L"Text_PUSH");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_SELECT.png", L"Text_SELECT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_SHUT.png", L"Text_SHUT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_SINK.png", L"Text_SINK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_STOP.png", L"Text_STOP");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_WIN.png", L"Text_WIN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Text_YOU.png", L"Text_YOU");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_BRICK.png", L"Tile_BRICK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_FORT.png", L"Tile_FORT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_GRASS.png", L"Tile_GRASS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_HEDGE.png", L"Tile_HEDGE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_LAVA.png", L"Tile_LAVA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_ROAD.png", L"Tile_ROAD");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_RUBBLE.png", L"Tile_RUBBLE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_WALL.png", L"Tile_WALL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Tile_WATER.png", L"Tile_WATER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap.png", L"WORLDMAP");
}

void CMainGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneManager::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
#pragma region  FPS 출력
	++m_iFPS;

	if (m_ullTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_ullTime = GetTickCount64();
	}
#pragma endregion

#pragma region 더블버퍼링 준비
	//화면 Rect
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	//HDC 
	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	HDC hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(m_hDC, OCX, OCY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);
	Graphics graphics(hMemDC);
	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
#pragma endregion

	//Render here
	CSceneManager::GetInstance()->Render(&graphics);

	//더블 버퍼링 결과물 출력
	//원본을 해상도에 맞게 확대하여 출력
	StretchBlt(m_hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, OCX, OCY, SRCCOPY);

	//메모리 할당해제
	/*SelectObject(hMemDC, oldBitmap);
	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC);*/
}

void CMainGame::Release()
{
	CSceneManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}
