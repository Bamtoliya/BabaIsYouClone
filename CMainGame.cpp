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
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"ObjectsCharacter-export.png", L"Character");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"ObjectsText-export.png", L"Text");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"ObjectsStatic-export.png", L"Static");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"ObjecttsTiled-export.png", L"Tiled");	
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"WorldMap.png", L"WorldMap");
	CResourceManager::GetInstance()->InsertImage(SPRITEPATH L"text_you_sheet.bmp", L"Text_You");
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
