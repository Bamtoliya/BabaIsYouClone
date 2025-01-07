#pragma once
#include "CWordBlock.h"
class CPropertyBlock : public CWordBlock
{
public:
	CPropertyBlock() { m_eBlock = BLOCKTYPE::PROPERTY; m_eProperty = PROPERTY::STOP; }
private:
	PROPERTY m_eProperty;
};

