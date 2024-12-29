#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject() : m_fSpeed(0.f), m_bDead(false), m_bActive(false), m_pTarget(nullptr), m_pImgKey(nullptr), m_bAnimate(false), m_eDir(DIRECTION::RIGHT)
{	
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(Rect));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

void CGameObject::UpdateRect()
{
	m_tRect = {
		INT(m_tInfo.fX),
		INT(m_tInfo.fY),
		INT(m_tInfo.fCX),
		INT(m_tInfo.fCY)
	};
}

void CGameObject::MoveFrame()
{
	if (g_bAnimate)
	{
		if (m_tFrame.ullTime + m_tFrame.ullSpeed < GetTickCount64())
		{
			++m_tFrame.iFrameStart;

			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = 0;
			m_tFrame.ullTime = GetTickCount64();
		}
	}
}
