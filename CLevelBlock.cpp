#include "pch.h"
#include "CLevelBlock.h"
#include "CLevel00.h"
#include "Designs.h"

void CLevelBlock::Initialize()
{
	m_level = new CLevel00;
	m_szTitle = L"BABAISYOU";
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
	if (m_level)
	{
		//Transition();
		CSceneManager::GetInstance()->SetStage(m_level);
	}
}

void CLevelBlock::Exit()
{
}

void CLevelBlock::Clear()
{
}

void CLevelBlock::Transition(Graphics* g)
{
	//ChangeImageColor(image1, )
	/*Image* image1;
	Image* image2;
	Image* image3;
	Image* image4;

	Image* image5;
	Image* image6;*/
}