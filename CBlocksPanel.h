#pragma once
#include "CPanel.h"
class CBlocksPanel : public CPanel
{
public:
    CBlocksPanel() {}
    CBlocksPanel(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
    void Update() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
    void SetFocus(CUIElement* c);
    CUIElement* GetCurBlock() { return m_pCurFocus; }
private:
    CUIElement* m_pCurFocus;
    CUIElement* m_pPreFocus;
};

