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
	if (m_level->GetCleared()) m_bClear = true;
	__super::UpdateRect();
}

void CLevelBlock::LateUpdate()
{
	__super::MoveFrame();

}

void CLevelBlock::Render(Graphics* g)
{
	Image* image = CResourceManager::GetInstance()->FindImage(m_pImgKey);
	if (image)
	{
		int x;
		int y = y = 1 + m_tFrame.iFrameStart * 25;
		if (m_bClear) x = 1;
		else x = 26;
		g->DrawImage(image, m_tRect, x, y, 24, 24, UnitPixel);
	}
	else
	{
		SolidBrush brush(Color::Red);
		g->FillRectangle(&brush, m_tRect);
	}
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
	
}