#pragma once
class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame() { Release(); }

	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
protected:
private:
	HDC m_hDC;
#pragma region FPSÀç±â
	ULONG64		m_ullTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
#pragma endregion
};

