#pragma once
#include "CBlock.h"
class CObjectBlock : public CBlock
{
public:
	CObjectBlock() { m_eBlock = BLOCKTYPE::OBJECT; }
	~CObjectBlock() {}
private:
	bool m_bTile;
	bool m_bLeft;
	bool m_bRight;
	bool m_bUp;
	bool m_bDown;
};

