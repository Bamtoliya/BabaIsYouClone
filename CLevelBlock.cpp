#include "pch.h"
#include "CLevelBlock.h"
#include "Designs.h"

void CLevelBlock::Initialize()
{
}

void CLevelBlock::Update()
{
	__super::UpdateRect();
}

void CLevelBlock::LateUpdate()
{
	__super::MoveFrame();
}

void CLevelBlock::Render(Graphics* g)
{
	SolidBrush brush(Color::Red);
	g->FillRectangle(&brush, m_tRect);
}

void CLevelBlock::Render(HDC hDC)
{
}

void CLevelBlock::Enter()
{
	//CBlockManager::GetInstance()->LoadBlock(L"Data/Level00.dat");
}

void CLevelBlock::Exit()
{
}

void CLevelBlock::Clear()
{
}

void CLevelBlock::Transition()
{
}