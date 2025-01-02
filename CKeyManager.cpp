#include "pch.h"
#include "CKeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

bool IsWindowActive(HWND hWnd) {
	return GetFocus() == hWnd;
}

CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyManager::~CKeyManager()
{
}

bool CKeyManager::KeyPressing(int _iKey)
{
	if (IsWindowActive(g_hWnd) && GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyManager::KeyDown(int _iKey)
{
	if (IsWindowActive(g_hWnd) && (!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

bool CKeyManager::KeyUp(int _iKey)
{
	if (IsWindowActive(g_hWnd) && (m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

void CKeyManager::Update()
{
	
}

void CKeyManager::LateUpdate()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}
