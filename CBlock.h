#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
    CBlock() : m_eBlock(BLOCKTYPE::NONE), m_eWord(GAMEWORD::NONE), m_eNoun(NOUN::NONE), m_eVerb(VERB::NONE) { m_tInfo = { 0, 0, 24, 24 }; }
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
    void SetNoun(NOUN n) { m_eNoun = n; }
    void SetVerb(VERB v) { m_eVerb = v; }
    void AddProperty(PROPERTY p) { m_ePROPERTY.push_back(p); }
    //void RemoveProperty(PROPERTY p) { m_ePROPERTY.push_back(p); }
    BLOCKTYPE GetBlockType() { return m_eBlock; }
    NOUN GetNoun() { return m_eNoun; }
    VERB GetVerb() { return m_eVerb; }
    list<PROPERTY> GetProperties() { return m_ePROPERTY; }
    void Clone(CBlock& dst);
    
protected:
    void ChangeState();
    BLOCKTYPE		m_eBlock;
    GAMEWORD        m_eWord;
    NOUN            m_eNoun;
    VERB            m_eVerb;
    list<PROPERTY>  m_ePROPERTY;
};

