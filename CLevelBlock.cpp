#include "pch.h"
#include "CLevelBlock.h"

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