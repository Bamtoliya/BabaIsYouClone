#pragma once
class CTileManager
{
public:
	static CTileManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileManager;

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
	static CTileManager* m_pInstance;
};

