#pragma once
#include "CLevel.h"
class CLevel00 : public CLevel
{
public:
    CLevel00() { m_szTitle = L"BABA IS YOU"; }
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;
    void Restart() override;
private:
    void KeyInput();
    Color m_color;
    float m_fTime;
    bool m_bTransition;
};

