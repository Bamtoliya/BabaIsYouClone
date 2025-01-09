#include "pch.h"
#include "CBlockManager.h"
#include "Designs.h"

CBlockManager* CBlockManager::m_pInstance = nullptr;

CBlockManager::CBlockManager()
{
	m_iWidth = 10;
	m_iHeight = 10;
	m_levelGrid.SetWidth(m_iWidth);
	m_levelGrid.SetHeight(m_iHeight);
	m_levelGrid.Initialize();
}

void CBlockManager::Initialize()
{
	m_levelGrid.SetWidth(m_iWidth);
	m_levelGrid.SetHeight(m_iHeight);
	m_levelGrid.Initialize();
}

void CBlockManager::Update()
{
	m_levelGrid.Update();
}

void CBlockManager::LateUpdate()
{
	m_levelGrid.LateUpdate();
}

void CBlockManager::Render(Graphics* g)
{
	m_levelGrid.Render(g);
}

void CBlockManager::Render(HDC hDC)
{

}

void CBlockManager::Release()
{
	
}

void CBlockManager::PickBlock(Point pt, CBlock b)
{
	float startX = startX = OCX / 2.f - m_iWidth / 2.f * TILECX;
	float startY = startY = OCY / 2.f - m_iHeight / 2.f * TILECY;

	int	x = (pt.X - startX) / TILECX;
	int	y = (pt.Y - startY) / TILECY;

	if (0 > x || (size_t)x >= m_levelGrid.GetWidth())
		return;
	if (0 > y || (size_t)y >= m_levelGrid.GetHeight())
		return;
	m_levelGrid.EditBlock(b, x, y);
}

void CBlockManager::SaveBlock()
{
	
	HANDLE hFile = CreateFile(L"Data/Level_PUSH.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	int		iWidth(0), iHeight(0);
	DWORD	dwByte(0);
	iWidth = m_levelGrid.GetWidth();
	iHeight = m_levelGrid.GetHeight();
	WriteFile(hFile, &iWidth, sizeof(int), &dwByte, NULL);
	WriteFile(hFile, &iHeight, sizeof(int), &dwByte, NULL);
	for (int i = 0; i < iHeight; ++i)
	{
		for (int j = 0; j < iWidth; ++j)
		{
			for (auto& g : m_levelGrid.GetGrid()[i][j]->GetList())
			{
				BLOCKTYPE eType = g->GetBlockType();
				const TCHAR* szImgKey = g->GetImgKey();
				int nLen = _tcslen(szImgKey) + 1;
				INFO info = g->GetInfo();
				WriteFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				WriteFile(hFile, &eType, sizeof(BLOCKTYPE), &dwByte, NULL);
				WriteFile(hFile, &nLen, sizeof(int), &dwByte, NULL);
				WriteFile(hFile, szImgKey, nLen * sizeof(TCHAR), &dwByte, NULL);
			}
		}
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Level Save", L"성공", MB_OK);
}

void CBlockManager::LoadBlock()
{
	HANDLE hFile = CreateFile(L"Data/Level_PUSH.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD	dwByte(0);

	Release();

	ReadFile(hFile, &m_iWidth, sizeof(int), &dwByte, NULL);
	ReadFile(hFile, &m_iHeight, sizeof(int), &dwByte, NULL);
	m_levelGrid.SetWidth(m_iWidth);
	m_levelGrid.SetHeight(m_iHeight);
	m_levelGrid.Initialize();

	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& g : m_levelGrid.GetGrid()[i][j]->GetList())
			{
				BLOCKTYPE eType;
				
				INFO info;
				int nLen;
				ReadFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				ReadFile(hFile, &eType, sizeof(BLOCKTYPE), &dwByte, NULL);
				ReadFile(hFile, &nLen, sizeof(int), &dwByte, NULL); // 길이 읽기
				TCHAR* szImgKey = new TCHAR[nLen+1];
				ReadFile(hFile, szImgKey, nLen * sizeof(TCHAR), &dwByte, NULL);
				g->SetPos(info.fX, info.fY);
				g->SetSize(info.fCX, info.fCY);
				g->SetImgKey(szImgKey);
				switch (eType)
				{
				case BLOCKTYPE::NOUN:
				case BLOCKTYPE::VERB:
				case BLOCKTYPE::PROPERTY:
					g->AddProperty(PROPERTY::PUSH);
					break;
				}
				g->SetBlockType(eType);
				if (0 == dwByte)
					break;
			}
		}
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Level Load", L"성공", MB_OK);
}

void CBlockManager::LoadBlock(CGrid& dst, const TCHAR* filepath)
{
	HANDLE hFile = CreateFile(filepath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD	dwByte(0);

	Release();

	ReadFile(hFile, &m_iWidth, sizeof(int), &dwByte, NULL);
	ReadFile(hFile, &m_iHeight, sizeof(int), &dwByte, NULL);
	dst.SetWidth(m_iWidth);
	dst.SetHeight(m_iHeight);
	dst.Initialize();

	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& g : dst.GetGrid()[i][j]->GetList())
			{
				BLOCKTYPE eType;
				NOUN n;
				VERB v;
				INFO info;
				int nLen;
				ReadFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				ReadFile(hFile, &eType, sizeof(BLOCKTYPE), &dwByte, NULL);
				ReadFile(hFile, &nLen, sizeof(int), &dwByte, NULL); // 길이 읽기
				TCHAR* szImgKey = new TCHAR[nLen + 1];
				ReadFile(hFile, szImgKey, nLen * sizeof(TCHAR), &dwByte, NULL);
				/*ReadFile(hFile, &n, sizeof(NOUN), &dwByte, NULL);
				ReadFile(hFile, &v, sizeof(VERB), &dwByte, NULL);*/
				g->SetPos(info.fX, info.fY);
				g->SetSize(info.fCX, info.fCY);
				g->SetImgKey(szImgKey);
				g->SetBlockType(eType);
				switch (eType)
				{
				case BLOCKTYPE::NOUN:
				case BLOCKTYPE::VERB:
				case BLOCKTYPE::PROPERTY:
					g->AddProperty(PROPERTY::PUSH);
					break;
				}
				if (0 == dwByte)
					break;
			}
		}
	}
	CloseHandle(hFile);
}


