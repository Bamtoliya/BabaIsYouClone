#include "pch.h"
#include "CGrid.h"
#include "Designs.h"

CGrid::CGrid() : m_iWidth(33), m_iHeight(18), m_vCenter(OCX / 2, OCY / 2)
{
	m_grid.reserve(m_iWidth * m_iHeight);
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid.push_back(CBlock(startX + j * TILECX, startY + i * TILECY, L"TEXT_YOU", BLOCKTYPE::TEXT));
		}
	}
}

void CGrid::Render(Graphics* g)
{
	Pen pen(Color(125, 0, 255, 0), 1);
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	int endX = m_vCenter.x + TILECX * m_iWidth / 2.f;
	int endY = m_vCenter.y + TILECY * m_iHeight / 2.f;

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
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i * m_iWidth + j].Render(g);
		}
	}
	Image* image = CResourceManager::GetInstance()->FindImage(L"CURSOR");
	g->DrawImage(image, Rect(startX + 24 -4, startY + 24-4, 32, 32), 1, 1, 32, 32, UnitPixel);
}