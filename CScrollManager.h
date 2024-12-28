#pragma once
class CScrollManager
{
private:
	CScrollManager();
	~CScrollManager();

public:
	float			GetScrollX() { return m_fScrollX; }
	float			GetScrollY() { return m_fScrollY; }

	void			SetScrollX(float _fX) { m_fScrollX += _fX; }
	void			SetScrollY(float _fY) { m_fScrollY += _fY; }

	void			ScrollLock();

public:
	static CScrollManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CScrollManager;
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
	static CScrollManager* m_pInstance;

	float			    m_fScrollX;
	float			    m_fScrollY;
};

