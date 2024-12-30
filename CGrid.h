#pragma once
#include "Designs.h"
#include "Blocks.h"
class CGrid
{
public:
	CGrid() {}
	virtual ~CGrid() {};

	vector<CBlock> m_grid;
	int m_iWidth;
	int m_iHeight;
};

