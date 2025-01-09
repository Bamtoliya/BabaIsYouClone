#pragma once
#include "CLevel.h"
class CLevel00 : public CLevel
{
public:
    CLevel00() { m_szTitle = L"BABA IS YOU"; m_color = Color(255, 21, 24, 31); }
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;
    void Restart() override;
private:
    void KeyInput();
    bool m_bTransition;
};

