#include "pch.h"
#include "Designs.h"


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
	m_eCurScene = eID;
	if (m_ePreScene != m_eCurScene)
	{
		m_bInStage = false;
		
		SafeDelete(m_pScene);
		switch (eID)
		{
		case SCENEID::Menu:
			m_pScene = new CMenu;
			break;
		case SCENEID::Game:
			m_pScene = new CInGame;
			break;
		case SCENEID::Test:
			m_pScene = new CTestScene;
			break;
		case SCENEID::Edit:
			m_pScene = new CEdit;
			break;
		case SCENEID::End:
			break;
		default:
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneManager::SetStage(CLevel* level)
{
	if (m_eCurScene == SCENEID::Game)
	{
		if (level)
		{
			dynamic_cast<CInGame*>(m_pScene)->SetInLevel(true);
			dynamic_cast<CInGame*>(m_pScene)->SetInWorld(false);
			dynamic_cast<CInGame*>(m_pScene)->SetLevel(level);
		}
		else
		{
			dynamic_cast<CInGame*>(m_pScene)->SetInLevel(false);
			dynamic_cast<CInGame*>(m_pScene)->SetInWorld(true);
			dynamic_cast<CInGame*>(m_pScene)->SetLevel(nullptr);
		}
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

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneManager::Release()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
