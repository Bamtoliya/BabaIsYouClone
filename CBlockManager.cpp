#include "pch.h"
#include "CBlockManager.h"
#include "Designs.h"

CBlockManager* CBlockManager::m_pInstance = nullptr;

CBlockManager::CBlockManager()
{
	m_vecBlock.reserve(TILEX * TILEY);
	m_iWidth = 10;
	m_iHeight = 10;
}

void CBlockManager::Initialize()
{
	int hW = m_iWidth / 2;
	int hH = m_iHeight / 2;
	for (int i = -hW; i < hW; ++i)
	{
		for (int j = -hH; j < hH; ++j)
		{
			float fX = OCX / 2 + (float)(i * TILECX);
			float fY = OCY / 2 + (float)(j * TILECY);

			CGameObject* pTile = CAbstractFactory<CBlock>::Create(fX, fY);
			m_vecBlock.push_back(pTile);
		}
	}
}

void CBlockManager::Update()
{
	for (auto& pTile : m_vecBlock)
		if(pTile) pTile->Update();
}

void CBlockManager::LateUpdate()
{
	for (auto& pTile : m_vecBlock)
		if(pTile) pTile->LateUpdate();
}

void CBlockManager::Render(Graphics* g)
{
	//DrawGrid
	Pen pen(Color::White);
	
	for (auto& pTile : m_vecBlock)
		if(pTile) pTile->Render(g);
}

void CBlockManager::Render(HDC hDC)
{
	//if (g_bDevmode)
	//{
	//	Pen pen(Color::White);
	//	//DrawGrid
	//	for (int j = 1; j < TILEX - 1; ++j)
	//	{
	//		g->DrawLine(&pen, Point(j * TILECX, 0), Point(j * TILECX, WINCY));
	//	}
	//	for (int i = 1; i < TILEY - 1; ++i)
	//	{
	//		g->DrawLine(&pen, Point(0, i * TILECY), Point(WINCX, i * TILECY));
	//	}
	//}
	for (auto& pTile : m_vecBlock)
		pTile->Render(hDC);
}

void CBlockManager::Release()
{
	for_each(m_vecBlock.begin(), m_vecBlock.end(), SafeDelete<CGameObject*>);
	m_vecBlock.clear();
}

void CBlockManager::PickBlock(Point pt, PROPERTY pp)
{
	int		x = pt.X / TILECX;
	int		y = pt.Y / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecBlock.size())
		return;
	//m_vecBlock[iIndex]->SetDrawID(iDrawID);
}

void CBlockManager::SaveBlock()
{
	HANDLE hFile = CreateFile(L"../Data/Level.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	int		iDrawID(0), iOption(0);
	DWORD	dwByte(0);

	for (auto& pTile : m_vecBlock)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->GetDrawID();
		iOption = dynamic_cast<CTile*>(pTile)->GetOption();

		WriteFile(hFile, pTile->GetInfoPointer(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Level Save", L"성공", MB_OK);
}

void CBlockManager::LoadBlock()
{
	HANDLE hFile = CreateFile(L"../Data/Level.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	int		iDrawID(0), iOption(0);
	DWORD	dwByte(0);
	INFO	tInfo{};

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CGameObject* pBlcok = CAbstractFactory<CBlock>::Create(tInfo.fX, tInfo.fY);
		/*dynamic_cast<CTile*>(pTile)->SetDrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->SetOption(iOption);*/

		m_vecBlock.push_back(pBlcok);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Level Load", L"성공", MB_OK);
}


