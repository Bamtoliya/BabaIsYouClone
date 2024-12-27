#pragma once
class CSoundManager
{
public:
	static CSoundManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CSoundManager;
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
private:
	static CSoundManager* m_pInstance;
};

