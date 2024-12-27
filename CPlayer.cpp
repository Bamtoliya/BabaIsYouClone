#include "pch.h"
#include "CPlayer.h"
#include "Designs.h"

enum STATE { IDLE, WALK, HIT, DEAD, END };

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f };
	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
	KeyInput();
	ChangeMotion();
	__super::UpdateRect();
}

void CPlayer::LateUpdate()
{

	__super::MoveFrame();
}

void CPlayer::Render(Graphics* graphic)
{
	if (g_bDevmode)
	{
		Pen pen(Color::Green);
		graphic->DrawRectangle(&pen, m_tRect);
	}
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{

	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{

	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
	{

	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
	{

	}
}

void CPlayer::ChangeMotion()
{

}
