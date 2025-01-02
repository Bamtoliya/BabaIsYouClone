#pragma once
#include "CBlock.h"
class CCursor : public CBlock
{
public:
    CCursor() { m_tInfo = { 0, 0, 32, 32 }; m_pImgKey = L"CURSOR"; m_tFrame = { 0, 0, 2, 0, 200, GetTickCount64() }; }
    ~CCursor() { Release(); }
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollision(CGameObject* op) override;
};

