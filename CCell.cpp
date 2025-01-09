#include "pch.h"
#include "CCell.h"

void CCell::Update()
{
	for (auto& e : m_blocks)
	{
		e->SetPos(m_tInfo.fX, m_tInfo.fY);
		for (auto& t : e->GetProperties())
		{
			if (t == PROPERTY::STOP)
			{
				m_bCanMove = false;
			}
			else if (t == PROPERTY::PUSH)
			{
				m_bCanPush = true;
			}
			else
			{
				m_bCanMove = true;
				m_bCanPush = false;
			}

		}
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

void CCell::ClearBlocks()
{
	m_blocks.clear();
}
