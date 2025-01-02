#pragma once
#include "CBlock.h"
#include "CCell.h"
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
	void SetCenter(Vector2 c) { m_vCenter = c; }
	void Move(DIRECTION dir);
	void MoveBlock(CBlock* b, int x, int y);
	void AddBlock(CBlock* b, int x, int y);
	void Open();
	void CheckSentence();
	void EnterLevel(CBlock* cursor);
private:
	vector<vector<CCell>> m_grid;
	int m_iWidth;
	int m_iHeight;
	int m_TileCX;
	int m_TileCY;
	Vector2 m_vCenter;
	DIRECTION m_eDir;
};

