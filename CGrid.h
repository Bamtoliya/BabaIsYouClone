#pragma once
#include "CBlock.h"
class CGrid
{
public:
	CGrid();
	~CGrid() {}
	void Render(Graphics* g);
	void SetWidth(int w) { m_iWidth = w; }
	void SetHeight(int h) { m_iHeight = h; }
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	void SetCenter(Vector2 c) { m_vCenter = c; }
private:
	vector<CBlock> m_grid;
	int m_iWidth;
	int m_iHeight;
	Vector2 m_vCenter;
};

