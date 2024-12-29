#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
    CBlock() : m_pImgKey(nullptr), m_eBlock(BLOCKTYPE::NONE), m_eWord(GAMEWORD::NONE), m_eNoun(NOUN::NONE), m_eVerb(VERB::NONE) {}
    virtual ~CBlock() {};
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollision(CGameObject* op) override;
private:
    void ChangeState();
    BLOCKTYPE		m_eBlock;
    GAMEWORD        m_eWord;
    NOUN            m_eNoun;
    VERB            m_eVerb;
    list<PROPERTY>  m_ePROPERTY;
    const TCHAR*    m_pImgKey;
};

