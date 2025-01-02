#pragma once
#include "CMenuButton.h"
class CMainMenuUI : public CUIElement
{
public:
	CMainMenuUI();
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
	CMenuButton* GetCurFocus() { return m_curFocus; }
	void SetCurFocus(CMenuButton* b) { m_curFocus = b; }
private:
	void KeyInput();
	CMenuButton* m_curFocus;
	int m_iFocusIndex;
};