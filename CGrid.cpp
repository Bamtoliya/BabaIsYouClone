#include "pch.h"
#include "CGrid.h"
#include "Designs.h"

CGrid::CGrid() : m_iWidth(33), m_iHeight(18), m_vCenter(OCX / 2, OCY / 2)
{
	m_grid = vector<vector<CCell>>(m_iHeight, vector<CCell>(m_iWidth));
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j] = CCell();
			m_grid[i][j].SetInfo(startX + j * TILECX, startY + i * TILECY);
			m_grid[i][j].SetIndex(i, j);
			if (i == 0 && j == 0)
			{
				m_grid[i][j].AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"TEXT_CHARACTER_BABA", BLOCKTYPE::CHARACTER));
			}
			else {
				m_grid[i][j].AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"", BLOCKTYPE::NONE));
			}
			
		}
	}
}

void CGrid::Initialize()
{
}

void CGrid::Update()
{
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j].Update();
		}
	}
	KeyInput();
}

void CGrid::LateUpdate()
{
	for (int i = 0; i < m_iHeight; ++i)
	{	
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j].LateUpdate();
		}
	}
}

void CGrid::Render(Graphics* g)
{
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	int endX = m_vCenter.x + TILECX * m_iWidth / 2.f;
	int endY = m_vCenter.y + TILECY * m_iHeight / 2.f;
#pragma region 그리드 표현
	Pen pen(Color(125, 0, 255, 0), 1);
	if (g_bDevmode)
	{
		//세로선
		for (int i = 0; i <= m_iWidth; ++i)
		{
			g->DrawLine(&pen, Point(startX + i * TILECX, startY), Point(startX + i * TILECX, endY));
		}
		//가로선
		for (int i = 0; i <= m_iHeight; ++i)
		{
			g->DrawLine(&pen, Point(startX, startY + i * TILECY), Point(endX, startY + i * TILECY));
		}
	}
#pragma endregion

	
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j].Render(g);
		}
	}
	Image* image = CResourceManager::GetInstance()->FindImage(L"CURSOR");
	g->DrawImage(image, Rect(startX + 20 , startY + 20, 32, 32), 1, 1, 32, 32, UnitPixel);
}

void CGrid::Render(HDC hDC)
{
}

void CGrid::Move(DIRECTION dir)
{
	vector<CBlock*> toMove;
	int x = 0;
	int y = 0;
	for (auto& e : m_grid)
	{
		for (auto& t : e)
		{
			for (auto& b : t.GetList())
			{
				auto l = b->GetBlockType();

				if (l == BLOCKTYPE::CHARACTER)
				{
					x = t.GetXIndex();
					y = t.GetYIndex();
					MoveBlock(b, x, y);
				}
			}
		}
	}
}

void CGrid::MoveBlock(CBlock* b, int x, int y)
{
	switch (m_eDir)
	{
	case DIRECTION::LEFT:
		m_grid[y][x - 1].AddBlock(b);
		m_grid[y][x].RemoveBlock(b);
		break;
	case DIRECTION::RIGHT:
		m_grid[y][x + 1].AddBlock(b);
		m_grid[y][x].RemoveBlock(b);
		break;
	case DIRECTION::UP:
		break;
	case DIRECTION::DOWN:
		break;
	}
}

void CGrid::Open()
{

}

void CGrid::CheckSentence()
{
	for (auto& e : m_grid)
	{
		//if(e.GetList().)
	}
}

void CGrid::KeyInput()
{
	m_eDir = DIRECTION::NONE;
	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_eDir = DIRECTION::LEFT;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_eDir = DIRECTION::RIGHT;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
	{
		m_eDir = DIRECTION::UP;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
	{
		m_eDir = DIRECTION::DOWN;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_RETURN))
	{
	}
	Move(m_eDir);
}
