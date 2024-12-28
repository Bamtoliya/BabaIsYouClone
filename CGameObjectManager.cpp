#include "pch.h"
#include "Designs.h"

CGameObjectManager* CGameObjectManager::m_pInstance = nullptr;

CGameObject* CGameObjectManager::GetTarget(OBJID eID, CGameObject* pDst)
{
	return nullptr;
}

void CGameObjectManager::AddObject(OBJID eID, CGameObject* pObj)
{
	if (OBJID::END <= eID || nullptr == pObj)
		return;

	m_list[eID].push_back(pObj);
}

int CGameObjectManager::Update()
{
	for (size_t i = 0; i < OBJID::END; ++i)
	{
		for (auto iter = m_list[i].begin();
			iter != m_list[i].end(); )
		{
			(*iter)->Update();
			++iter;
			/*int iResult = ;

			if (OBJ_DEAD == iResult)
			{
				SafeDelete<CGameObject*>(*iter);
				iter = m_list[i].erase(iter);
			}
			else
				++iter;*/
		}
	}
	
	return 0;
}

void CGameObjectManager::LateUpdate()
{
	for (size_t i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_list[i])
		{
			pObj->LateUpdate();

			if (m_list[i].empty())
				break;

			/*RENDERID	eID = pObj->Get_GroupID();
			m_RenderList[eID].push_back(pObj);*/
		}
	}
	CCollisionManager::CollisionRect(m_list[OBJID::BLOCK], m_list[OBJID::BLOCK]);
}

void CGameObjectManager::Render(Graphics* g)
{
	for (size_t i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_list[i])
			pObj->Render(g);
	}
}

void CGameObjectManager::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_list[i])
			pObj->Render(hDC);
	}
}

void CGameObjectManager::Release()
{
	for (size_t i = 0; i < OBJID::END; ++i)
	{
		for_each(m_list[i].begin(), m_list[i].end(), SafeDelete<CGameObject*>);
		m_list[i].clear();
	}
}

//void CGameObjectManager::DeleteID(OBJID eID)
//{
//}
