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
    void RemoveProperty(PROPERTY p) { m_eProperties.erase(p); }
    BLOCKTYPE GetBlockType() { return m_eBlock; }
    set<PROPERTY> GetProperties() { return m_eProperties; }
    void Clone(CBlock& dst);
    void ChangeState();
    void UpdateWord();
    void Activate() { m_bActive = true; }
    void InActive() { m_bActive = false; }
    void Apply(CBlock* b);
    bool* GetTileNeihbor() { return m_bNeighbor; }
    void TileAssign(int& x);
    void IncreaseFrameAnimation() 
    { 
        ++m_tFrame.iFrameAnimation;
        if (m_tFrame.iFrameAnimation > 3)
            m_tFrame.iFrameAnimation = 0;
    }
protected:
    BLOCKTYPE		m_eBlock;
    set<PROPERTY>   m_eProperties;
    bool            m_bNeighbor[4];
};

