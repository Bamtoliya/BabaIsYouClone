#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
    CBlock() : m_eBlock(BLOCKTYPE::NONE) { m_pImgKey = L"", m_tInfo = {0, 0, 24, 24}; }
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
    void AddProperty(PROPERTY p) { m_eProperties.insert(p); }
    //void RemoveProperty(PROPERTY p) { m_ePROPERTY.push_back(p); }
    BLOCKTYPE GetBlockType() { return m_eBlock; }
    set<PROPERTY> GetProperties() { return m_eProperties; }
    void Clone(CBlock& dst);
    void ChangeState();
    void UpdateWord();
    void Activate() { m_bActive = true; }
    void InActive() { m_bActive = false; }
    void Apply(CBlock* b);
    /*NOUN GetNoun() { return m_eNoun; }
    VERB GetVerb() { return m_eVerb; }
    PROPERTY GetProperty() { return m_eProperty; }
    void SetWordType(GAMEWORD w) { m_eWord = w; }
    void SetNoun(NOUN n) { m_eNoun = n; }
    void SetVerb(VERB v) { m_eVerb = v; }
    void SetProperty(PROPERTY p) { m_eProperty = p; }*/
protected:
    BLOCKTYPE		m_eBlock;
    bool            m_bProperty[static_cast<int>(PROPERTY::END)];
    set<PROPERTY>   m_eProperties;
};

