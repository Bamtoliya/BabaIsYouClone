#pragma once
#include "pch.h"
#include "CLevel.h"
#include "CGrid.h"
#include "CLevel00.h"
class CLevelBlock : public CBlock
{
public:
	CLevelBlock() { m_level = new CLevel00; m_tInfo = { 0, 0, 24, 24 }; m_szTitle = L"BABA IS YOU"; m_eBlock = BLOCKTYPE::LEVEL; m_tFrame = { 0, 0, 2, 0, 200, GetTickCount64() }; }
	CLevelBlock(CLevel* l) { m_level = l; m_tInfo = { 0, 0, 24, 24 }; m_szTitle = l->GetTitle(); m_eBlock = BLOCKTYPE::LEVEL; m_tFrame = {0, 0, 2, 0, 200, GetTickCount64()}; }
	~CLevelBlock() {}
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(Graphics* g);
	virtual void Render(HDC hDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Clear();
	CGrid GetGrid();
	const TCHAR* GetTitle() { return m_szTitle; }
private:
	virtual void Transition(Graphics* g);
	CLevel* m_level;
	Color m_color;
	Image* m_pImage;
	bool m_bClear;
	const TCHAR* m_szTitle;
};

