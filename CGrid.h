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
	void Load();
	void SetWidth(int w) { m_iWidth = w; }
	void SetHeight(int h) { m_iHeight = h; }
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	void SetCenter(Vector2 c) { m_vCenter = c; }
	void Move(DIRECTION dir);
	void MoveBlock(CBlock* b, int x, int y);
	void Open();
	void CheckSentence();
	
private:
	void KeyInput();
	vector<vector<CCell>> m_grid;
	int m_iWidth;
	int m_iHeight;
	
	Vector2 m_vCenter;
	DIRECTION m_eDir;
};

