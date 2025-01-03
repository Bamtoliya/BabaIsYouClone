#include "pch.h"
#include "CMainGame.h"
#include "Designs.h"

bool g_bAnimate;

CMainGame::CMainGame()
	: m_hDC(GetDC(g_hWnd)), m_ullTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
	SetICMMode(m_hDC, ICM_ON);
}

void CMainGame::Initialize()
{
	g_bAnimate = false;
	InsertResources();
	cout << "CMainGame Initialized\n";
	CSceneManager::GetInstance()->SetScene(SCENEID::Test);
}

void CMainGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneManager::GetInstance()->LateUpdate();
	CKeyManager::GetInstance()->LateUpdate();
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
	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	HDC hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(m_hDC, OCX, OCY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);
	Graphics graphics(hMemDC);
	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
#pragma endregion

	//Render here
	//CSceneManager::GetInstance()->Render(hMemDC);
	CSceneManager::GetInstance()->Render(&graphics);

	//더블 버퍼링 결과물 출력
	//원본을 해상도에 맞게 확대하여 출력
	StretchBlt(m_hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, OCX, OCY, SRCCOPY);

	//메모리 할당해제
	SelectObject(hMemDC, oldBitmap);
	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC);
}

void CMainGame::Release()
{
	CSceneManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::InsertResources()
{
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_CHARACTER_BABA.png", L"TEXT_CHARACTER_BABA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_CHARACTER_KEKE.png", L"TEXT_CHARACTER_KEKE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_BOX.png", L"TEXT_OBJECT_BOX");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CIRCLE.png", L"CIRCLE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CURSOR.png", L"CURSOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_DOOR.png", L"TEXT_OBJECT_DOOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_DUST.png", L"TEXT_OBJECT_DUST");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_FLAG.png", L"TEXT_OBJECT_FLAG");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_FLOWER.png", L"TEXT_OBJECT_FLOWER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"FOCUS.png", L"FOCUS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_FOLIAGE.png", L"TEXT_OBJECT_FOLIAGE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_JELLY.png", L"TEXT_OBJECT_JELLY");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_KEY.png", L"TEXT_OBJECT_KEY");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_LOVE.png", L"TEXT_OBJECT_LOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_PILLAR.png", L"TEXT_OBJECT_PILLAR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_ROCK.png", L"TEXT_OBJECT_ROCK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_SKULL.png", L"TEXT_OBJECT_SKULL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_STAR.png", L"TEXT_OBJECT_STAR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OBJECT_STAR2.png", L"TEXT_OBJECT_STAR2");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_AND.png", L"TEXT_AND");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_DEFEAT.png", L"TEXT_DEFEAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_END.png", L"TEXT_END");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_FLOAT.png", L"TEXT_FLOAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_HOT.png", L"TEXT_HOT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_IS.png", L"TEXT_IS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_MELT.png", L"TEXT_MELT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_MOVE.png", L"TEXT_MOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_OPEN.png", L"TEXT_OPEN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_PULL.png", L"TEXT_PULL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_PUSH.png", L"TEXT_PUSH");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_SELECT.png", L"TEXT_SELECT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_SHUT.png", L"TEXT_SHUT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_SINK.png", L"TEXT_SINK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_STOP.png", L"TEXT_STOP");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_WIN.png", L"TEXT_WIN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_YOU.png", L"TEXT_YOU");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_BRICK.png", L"TEXT_TILE_BRICK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_CLOUDW.png", L"TEXT_TILE_CLOUDW");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_FORT.png", L"TEXT_TILE_FORT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_GRASS.png", L"TEXT_TILE_GRASS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_HEDGE.png", L"TEXT_TILE_HEDGE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_LAVA.png", L"TEXT_TILE_LAVA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_ROAD.png", L"TEXT_TILE_ROAD");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_RUBBLE.png", L"TEXT_TILE_RUBBLE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_WALL.png", L"TEXT_TILE_WALL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_WATER.png", L"TEXT_TILE_WATER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap.png", L"WORLDMAP");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap1.png", L"WORLDMAP1");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_LINE.png", L"TEXT_TILE_LINE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_ALPHABET.png", L"TEXT_ALPHABET");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_NUMBER.png", L"TEXT_NUMBER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Title.png", L"Title");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"logo.png", L"LOGO");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"Back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"TEXT_YOU.bmp", L"TEXT_YOU");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"ObjectsText-export.bmp", L"TEXT");
}
