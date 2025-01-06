#pragma once
#include "CBlock.h"
#include "CCell.h"
#include "CRule.h"
class CGrid
{
public:
	CGrid();
	~CGrid() {}
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(Graphics* g);
	void Render(HDC hDC);
	void SetWidth(int w) { m_iWidth = w; }
	void SetHeight(int h) { m_iHeight = h; }
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	int GetSize();
	vector<vector<CCell*>> GetGrid() { return m_grid; }
	void SetCenter(Vector2 c) { m_vCenter = c; }
	void Move(DIRECTION dir);
	void Move(int x, int y);
	void MoveBlock(CBlock* b, int x, int y);
	void AddBlock(CBlock* b, int x, int y);
	void Open();
	void CheckSentence();
	void CheckTileNeighbor();
	void EnterLevel(CBlock* cursor);
	void EditBlock(CBlock b, int x, int y);
	void PrintLevel(CBlock* cursor, Graphics* g, int x, int y);
	Rect GetRect() { return m_tRect; }
	bool CheckCanMove(DIRECTION d, int x, int y);
	void ApplyRule(CRule& r);
private:
	void KeyInput();
	vector<vector<CCell*>> m_grid;
	vector<CRule> m_rules;
	int m_iWidth;
	int m_iHeight;
	int m_TileCX;
	int m_TileCY;
	Rect m_tRect;
	Color m_backgroundColor;
	Vector2 m_vCenter;
	DIRECTION m_eDir;
	ULONG64 m_ullDelay;
	ULONG64 m_ullLastInput;
};

