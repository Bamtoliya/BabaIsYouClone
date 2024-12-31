#pragma once
#include "CUIElement.h"
class CTitle : public CUIElement
{
public:
    CTitle();
    CTitle(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
    void Update() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
private:
    void MoveFrame();
    FRAME m_tFrame;
};

