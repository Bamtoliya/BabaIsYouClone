#pragma once
#include "CGrid.h"
#include "CLevel.h"
class CWorldMap
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(Graphics* g);
	virtual void Render(HDC hDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Clear();
private:
	void Transition(Graphics* g);
	void MoveCursor(int x, int y);
	void EnterLevel();
	void KeyInput();
	void MoveFrame();
	CGrid m_grid;
	Color m_color;
	FRAME m_tFrame;
	CBlock* m_Cursor;
	ULONG64 m_ullDelay;
	ULONG64 m_ullLastInput;
	Vector2 m_vCursor;
	float m_fTTime;
	bool m_bTransition;
};

