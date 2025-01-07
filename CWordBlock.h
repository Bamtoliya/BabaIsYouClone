#pragma once
#include "CBlock.h"
class CWordBlock : public CBlock
{
public:
	CWordBlock() { m_eProperties.insert(PROPERTY::PUSH); }
	~CWordBlock() {};
private:
	
};

