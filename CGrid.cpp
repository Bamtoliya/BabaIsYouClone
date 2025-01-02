#include "pch.h"
#include "CGrid.h"
#include "Designs.h"
#include "CLevelBlock.h"

CGrid::CGrid() : m_iWidth(33), m_iHeight(18), m_vCenter(OCX / 2, OCY / 2)
{
	m_grid = vector<vector<CCell*>>(m_iHeight, vector<CCell*>(m_iWidth));
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j] = new CCell();
			m_grid[i][j]->SetInfo(startX + j * TILECX, startY + i * TILECY);
			m_grid[i][j]->SetIndex(i, j);
			m_grid[i][j]->AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"", BLOCKTYPE::NONE));
		}
	}
}

void CGrid::Initialize()
{
	m_grid = vector<vector<CCell*>>(m_iHeight, vector<CCell*>(m_iWidth));
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j] = new CCell();
			m_grid[i][j]->SetInfo(startX + j * TILECX, startY + i * TILECY);
			m_grid[i][j]->SetIndex(i, j);
			m_grid[i][j]->AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"", BLOCKTYPE::NONE));
		}
	}
}

void CGrid::Update()
{
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j]->Update();
		}
	}
}

void CGrid::LateUpdate()
{
	for (int i = 0; i < m_iHeight; ++i)
	{	
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j]->LateUpdate();
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
			m_grid[i][j]->Render(g);
		}
	}
}

void CGrid::Render(HDC hDC)
{
}

void CGrid::Move(DIRECTION dir)
{
	vector<CBlock*> toMove;
	int x = 0;
	int y = 0;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& b : m_grid[i][j]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::CHARACTER)
				{
					x = j;
					y = i;
					toMove.push_back(b);
				}
			}
		}
	}

	for (auto& b : toMove)
	{
		switch (m_eDir)
		{
		case DIRECTION::LEFT:
			m_grid[y][x]->RemoveBlock(b);
			m_grid[y][x - 1]->AddBlock(b);
			break;
		case DIRECTION::RIGHT:
			m_grid[y][x]->RemoveBlock(b);
			m_grid[y][x + 1]->AddBlock(b);
			break;
		case DIRECTION::UP:
			m_grid[y][x]->RemoveBlock(b);
			m_grid[y - 1][x]->AddBlock(b);
			break;
		case DIRECTION::DOWN:
			m_grid[y][x]->RemoveBlock(b);
			m_grid[y + 1][x]->AddBlock(b);
			break;
		}
	}
}

void CGrid::MoveBlock(CBlock* b, int x, int y)
{
	vector<CBlock*> toMove;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == b)
				{

					if ((i + y >= 0 && i + y < m_iHeight) && (j + x >= 0 && j + x < m_iWidth))
					{
						toMove.push_back(t);
						index.push_back({ i, j });
						
					}
				}
			}
		}
	}
	for (int i = 0; i < toMove.size(); ++i)
	{
		m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
		m_grid[index[i].first + y][index[i].second + x]->AddBlock(toMove[i]);
	}
}

void CGrid::AddBlock(CBlock* b, int x, int y)
{
	m_grid[y][x]->AddBlock(b);
}

void CGrid::Open()
{

}

void CGrid::CheckSentence()
{
	for (auto& e : m_grid)
	{

	}
}

void CGrid::EnterLevel(CBlock* cursor)
{
	list<CBlock*> findLevel;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == cursor)
				{
					findLevel = m_grid[i][j]->GetList();
				}
			}
		}
	}

	for (auto& l : findLevel)
	{
		if (l->GetBlockType() == BLOCKTYPE::LEVEL)
		{
			dynamic_cast<CLevelBlock*>(l)->Enter();
		}
	}
}

void CGrid::EditBlock(CBlock b, int x, int y)
{
	m_grid[y][x]->GetList().back()->SetImgKey(b.GetImgKey());
	m_grid[y][x]->GetList().back()->SetBlockType(b.GetBlockType());
}
