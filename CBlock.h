#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
    CBlock() : m_eBlock(BLOCKTYPE::NONE), m_Word(nullptr) { m_pImgKey = L"", m_tInfo = {0, 0, 24, 24}; }
    CBlock(float fX, float fY, const TCHAR* pImgKey, BLOCKTYPE b); 
    virtual ~CBlock() {};
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollision(CGameObject* op) override;
    void SetBlockType(BLOCKTYPE b) { m_eBlock = b; }
    void AddProperty(PROPERTY p) { m_ePROPERTY.push_back(p); }
    //void RemoveProperty(PROPERTY p) { m_ePROPERTY.push_back(p); }
    BLOCKTYPE GetBlockType() { return m_eBlock; }
    list<PROPERTY> GetProperties() { return m_ePROPERTY; }
    void Clone(CBlock& dst);
    void ChangeState();
    void UpdateWord();
    void Activate() { m_bActive = true; }
    NOUN GetNoun() { return m_eNoun; }
    VERB GetVerb() { return m_eVerb; }
    PROPERTY GetProperty() { return m_eProperty; }
protected:
    BLOCKTYPE		m_eBlock;
    NOUN            m_eNoun;
    VERB            m_eVerb;
    PROPERTY        m_eProperty;
    const TCHAR*    m_Word;
    list<PROPERTY>  m_ePROPERTY;
};

