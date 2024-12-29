#pragma once
#include "CUIElement.h"
class CPanel : public CUIElement
{
public:
    CPanel() {}
    CPanel(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
    void Update() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
};

