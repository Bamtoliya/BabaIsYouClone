#pragma once
class CResourceManager
{
public:
	static CResourceManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CResourceManager;
		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	map<const TCHAR*, Image*> GetMap() { return m_mapImage; }
	void InsertImage(const TCHAR* pFIlePath, const TCHAR* pImgKey);
	Image* FindImage(const TCHAR* pImgKey);
	void Release();
private:
	static CResourceManager* m_pInstance;
	map<const TCHAR*, Image*>	m_mapImage;
};

