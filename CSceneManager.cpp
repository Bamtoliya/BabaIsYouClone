#include "pch.h"
#include "CSceneManager.h"
#include "CUIManager.h"
#include "CKeyManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

CSceneManager::CSceneManager() : m_pScene(nullptr), m_eCurScene(SCENEID::Menu), m_ePreScene(SCENEID::End)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::SetScene(SCENEID eID)
{
	switch (eID)
	{
	case SCENEID::Menu:
		break;
	case SCENEID::Game:
		break;
	case SCENEID::Test:
		break;
	case SCENEID::Edit:
		break;
	case SCENEID::End:
		break;
	default:
		break;
	}
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneManager::Render(Graphics* g)
{
	m_pScene->Render(g);
}

void CSceneManager::Release()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
