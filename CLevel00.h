#pragma once
#include "CLevel.h"
class CLevel00 : public CLevel
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void KeyInput();
    Color m_color;
    float m_fTime;
    bool m_bTransition;
    Rect m_tRect1;
    Rect m_tRect2;
    Rect m_tRect3;
    Rect m_tRect4;
};

