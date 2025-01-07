#pragma once
#include "CWordBlock.h"
class CNounBlock :
    public CWordBlock
{
public:
    CNounBlock() { m_eBlock = BLOCKTYPE::NOUN; }
};

