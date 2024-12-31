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
	for (int i = -hH; i < hH; ++i)
	{
		for (int j = -hW; j < hW; ++j)
		{
			float fX = OCX / 2 + (float)(j * TILECX);
			float fY = OCY / 2 + (float)(i * TILECY);

			CGameObject* pBlock = CAbstractFactory<CBlock>::Create(fX, fY);
			m_vecBlock.push_back(pBlock);
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
	Pen pen(Color::White);
	
	for (auto& pTile : m_vecBlock)
		if(pTile) pTile->Render(g);
}

void CBlockManager::Render(HDC hDC)
{
	for (auto& pTile : m_vecBlock)
		pTile->Render(hDC);
}

void CBlockManager::Release()
{
	for_each(m_vecBlock.begin(), m_vecBlock.end(), SafeDelete<CGameObject*>);
	m_vecBlock.clear();
}

void CBlockManager::PickBlock(Point pt, CBlock b)
{
	//그리드 시작좌표
	int startX	= OCX / 2 - m_iWidth / 2 * TILECX;
	int startY	= OCY / 2 - m_iHeight / 2 * TILECY;

	int	x = (pt.X - startX) / TILECX;
	int	y = (pt.Y - startY) / TILECY;
	int	iIndex = y * m_iWidth + x;
	printf("X: %d Y: %d\n", x, y);
	cout << iIndex << endl;

	if (0 > iIndex || (size_t)iIndex >= m_vecBlock.size())
		return;
	m_vecBlock[iIndex]->SetImgKey(b.GetImgKey());
	dynamic_cast<CBlock*>(m_vecBlock[iIndex])->SetBlockType(b.GetBlockType());
	dynamic_cast<CBlock*>(m_vecBlock[iIndex])->SetNoun(b.GetNoun());
	dynamic_cast<CBlock*>(m_vecBlock[iIndex])->SetVerb(b.GetVerb());
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
		//iDrawID = dynamic_cast<CBlock*>(pTile)->GetDrawID();
		//iOption = dynamic_cast<CBlock*>(pTile)->GetOption();

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

		//CBlock* pBlcok = CAbstractFactory<CBlock>::Create(tInfo.fX, tInfo.fY);
		/*dynamic_cast<CTile*>(pTile)->SetDrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->SetOption(iOption);*/

		//m_vecBlock.push_back(pBlcok);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Level Load", L"성공", MB_OK);
}


