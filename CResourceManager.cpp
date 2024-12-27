#include "pch.h"
#include "CResourceManager.h"

void CResourceManager::InsertImage(const TCHAR* pFIlePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapImage.begin(), m_mapImage.end(), FINDER(pImgKey));

	if (iter == m_mapImage.end())
	{
		Image* pImage = new Image(pFIlePath);
		m_mapImage.insert({ pImgKey, pImage });
	}
}

Image* CResourceManager::FindImage(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapImage.begin(), m_mapImage.end(), FINDER(pImgKey));

	if (iter == m_mapImage.end())
		return nullptr;

	return iter->second;
}

void CResourceManager::Release()
{
	for_each(m_mapImage.begin(), m_mapImage.end(), DeleteMap());
	m_mapImage.clear();
}
