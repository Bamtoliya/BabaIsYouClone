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
	CSceneManager::GetInstance()->SetScene(SCENEID::Menu);
	CSoundManager::GetInstance();
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
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_CHARACTER_BABA.png", L"NOUN_CHARACTER_BABA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_CHARACTER_KEKE.png", L"NOUN_CHARACTER_KEKE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_BOX.png", L"NOUN_OBJECT_BOX");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CIRCLE.png", L"CIRCLE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CURSOR.png", L"CURSOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_DOOR.png", L"NOUN_OBJECT_DOOR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_DUST.png", L"NOUN_OBJECT_DUST");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_FLAG.png", L"NOUN_OBJECT_FLAG");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_FLOWER.png", L"NOUN_OBJECT_FLOWER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"FOCUS.png", L"FOCUS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_FOLIAGE.png", L"NOUN_OBJECT_FOLIAGE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_JELLY.png", L"NOUN_OBJECT_JELLY");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_KEY.png", L"NOUN_OBJECT_KEY");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_LOVE.png", L"NOUN_OBJECT_LOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_PILLAR.png", L"NOUN_OBJECT_PILLAR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_ROCK.png", L"NOUN_OBJECT_ROCK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_SKULL.png", L"NOUN_OBJECT_SKULL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_STAR.png", L"NOUN_OBJECT_STAR");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_OBJECT_STAR2.png", L"NOUN_OBJECT_STAR2");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"CONNECTOR_AND.png", L"CONNECTOR_AND");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_DEFEAT.png", L"PROPERTY_DEFEAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_END.png", L"PROPERTY_END");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_FLOAT.png", L"PROPERTY_FLOAT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_HOT.png", L"PROPERTY_HOT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"VERB_IS.png", L"VERB_IS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_MELT.png", L"PROPERTY_MELT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_MOVE.png", L"PROPERTY_MOVE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_OPEN.png", L"PROPERTY_OPEN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_PULL.png", L"PROPERTY_PULL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_PUSH.png", L"PROPERTY_PUSH");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_SELECT.png", L"PROPERTY_SELECT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_SHUT.png", L"PROPERTY_SHUT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_SINK.png", L"PROPERTY_SINK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_STOP.png", L"PROPERTY_STOP");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_WIN.png", L"PROPERTY_WIN");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"PROPERTY_YOU.png", L"PROPERTY_YOU");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_BRICK.png", L"NOUN_TILE_BRICK");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_CLOUDW.png", L"NOUN_TILE_CLOUDW");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_FORT.png", L"NOUN_TILE_FORT");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_GRASS.png", L"NOUN_TILE_GRASS");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_HEDGE.png", L"NOUN_TILE_HEDGE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_LAVA.png", L"NOUN_TILE_LAVA");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_ROAD.png", L"NOUN_TILE_ROAD");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_RUBBLE.png", L"NOUN_TILE_RUBBLE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_WALL.png", L"NOUN_TILE_WALL");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_WATER.png", L"NOUN_TILE_WATER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap.png", L"WORLDMAP");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap1.png", L"WORLDMAP1");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"NOUN_TILE_LINE.png", L"NOUN_TILE_LINE");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_ALPHABET.png", L"TEXT_ALPHABET");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_NUMBER.png", L"TEXT_NUMBER");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"TEXT_TILE_X.png", L"TEXT_TILE_X");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_00.png", L"LEVEL_00");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_01.png", L"LEVEL_01");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_02.png", L"LEVEL_02");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_03.png", L"LEVEL_03");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_04.png", L"LEVEL_04");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_05.png", L"LEVEL_05");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_06.png", L"LEVEL_06");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"LEVEL_07.png", L"LEVEL_07");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"Title.png", L"Title");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"logo.png", L"LOGO");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"Back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"TEXT_YOU.bmp", L"TEXT_YOU");
	CBmpMgr::Get_Instance()->Insert_Bmp(SPRITEPATH L"ObjectsText-export.bmp", L"TEXT");
}
