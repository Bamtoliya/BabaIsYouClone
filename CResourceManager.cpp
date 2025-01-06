#include "pch.h"
#include "CResourceManager.h"

CResourceManager* CResourceManager::m_pInstance = nullptr;

void CResourceManager::InsertImage(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapImage.begin(), m_mapImage.end(), FINDER(pImgKey));

	if (iter == m_mapImage.end())
	{
		Image* pImage = new Image(pFilePath);
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

Vector2 CResourceManager::FindText(const TCHAR pTextKey)
{
	auto iter = find_if(m_mapText.begin(), m_mapText.end(), CHARFINDER(pTextKey));

	if (iter == m_mapText.end())
		return Vector2_zero;

	return iter->second;
}

void CResourceManager::Release()
{
	for_each(m_mapImage.begin(), m_mapImage.end(), DeleteMap());
	m_mapImage.clear();
}

CResourceManager::CResourceManager()
{
	
	m_mapText.emplace('A', Vector2{ 1, 1 });
	m_mapText.emplace('B', Vector2{51, 1});
	m_mapText.emplace('C', Vector2{101, 1});
	m_mapText.emplace('D', Vector2{151, 1});
	m_mapText.emplace('E', Vector2{201, 1});
	m_mapText.emplace('F', Vector2{251, 1});
	m_mapText.emplace('G', Vector2{301, 1});
	m_mapText.emplace('H', Vector2{1, 76});
	m_mapText.emplace('I', Vector2{51, 76});
	m_mapText.emplace('J', Vector2{101, 76});
	m_mapText.emplace('K', Vector2{151, 76});
	m_mapText.emplace('L', Vector2{201, 76});
	m_mapText.emplace('M', Vector2{251, 76});
	m_mapText.emplace('N', Vector2{301, 76});
	m_mapText.emplace('O', Vector2{1, 151});
	m_mapText.emplace('P', Vector2{51, 151});
	m_mapText.emplace('Q', Vector2{101, 151});
	m_mapText.emplace('R', Vector2{151, 151});
	m_mapText.emplace('S', Vector2{201, 151});
	m_mapText.emplace('T', Vector2{251, 151});
	m_mapText.emplace('U', Vector2{301, 151});
	m_mapText.emplace('V', Vector2{1, 226});
	m_mapText.emplace('W', Vector2{51, 226});
	m_mapText.emplace('X', Vector2{101, 226});
	m_mapText.emplace('Y', Vector2{151, 226});
	m_mapText.emplace('Z', Vector2{201, 226});
	m_mapText.emplace(' ', Vector2{251, 226});
	m_mapText.emplace('0', Vector2{1, 1});
	m_mapText.emplace('1', Vector2{51, 1});
	m_mapText.emplace('2', Vector2{101, 1});
	m_mapText.emplace('3', Vector2{151, 1});
	m_mapText.emplace('4', Vector2{201, 1});
	m_mapText.emplace('5', Vector2{1, 76});
	m_mapText.emplace('6', Vector2{51, 76});
	m_mapText.emplace('7', Vector2{101, 76});
	m_mapText.emplace('8', Vector2{151, 76});
	m_mapText.emplace('9', Vector2{201, 76});
}
