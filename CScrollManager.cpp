#include "pch.h"
#include "CScrollManager.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

CScrollManager::CScrollManager() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollManager::~CScrollManager()
{
}

void CScrollManager::ScrollLock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (WINCX - 1920.f > m_fScrollX)
		m_fScrollX = WINCX - 1920.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - 1280.f > m_fScrollY)
		m_fScrollY = WINCY - 1280.f;
}
