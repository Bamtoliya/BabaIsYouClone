#include "pch.h"
#include "CTile.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	m_tInfo = { 100, 100, 48, 48 };
}

void CTile::Update()
{
	__super::UpdateRect();
}

void CTile::LateUpdate()
{
	__super::MoveFrame();
}

void CTile::Render(Graphics* graphic)
{
	SolidBrush brush(Color::White);
	Pen pen(Color::White);
	graphic->DrawRectangle(&pen, m_tRect);
	//graphic->DrawRectangle(&brush, m_tRect);
}

void CTile::Release()
{
}

void CTile::OnCollision(CGameObject* op)
{
}
