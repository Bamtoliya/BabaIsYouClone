#include "pch.h"
#include "CCell.h"

void CCell::Update()
{
	for (auto& e : m_blocks)
	{
		e->SetPos(m_tInfo.fX, m_tInfo.fY);
		e->Update();
	}
}

void CCell::LateUpdate()
{
	for (auto& e : m_blocks)
	{
		e->LateUpdate();
	}
}

void CCell::Render(Graphics* graphic)
{
	for (auto& e : m_blocks)
	{
		e->Render(graphic);
	}
}

void CCell::Render(HDC hDC)
{
	for (auto& e : m_blocks)
	{
		e->Render(hDC);
	}
}

void CCell::Release()
{
	for_each(m_blocks.begin(), m_blocks.end(), SafeDelete<CBlock*>);
}

void CCell::SetInfo(int x, int y)
{
	m_tInfo = { (float)x, (float)y, TILECX, TILECY};
}

void CCell::AddBlock(CBlock* b)
{
	m_blocks.push_back(b);
}

void CCell::RemoveBlock(CBlock* b)
{
	m_blocks.remove_if([b](CBlock* block) { return block == b; });
}
