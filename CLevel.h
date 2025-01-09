#pragma once
#include "CGrid.h"
class CLevel
{
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(Graphics* g) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
	const TCHAR* GetTitle() { return m_szTitle; }
	bool GetCleared() { return m_bClear; }
	void SetCleared(bool c) { m_bClear = c; }
	virtual void Restart() PURE;
	virtual void SaveMove();
	virtual void Undo();
	virtual void WinTransition(Graphics* g);
protected:
	Color m_color;
	float m_fTime;
	stack<CGrid> m_undo;
	const TCHAR* m_szTitle;
	CGrid m_grid;
	bool m_bClear;
};

