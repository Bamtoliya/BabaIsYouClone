#pragma once
#include "CUIElement.h"
class CMainMenuUI : public CUIElement
{
	// CUIElement을(를) 통해 상속됨
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
};

