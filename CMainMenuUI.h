#pragma once
#include "CUIElement.h"
#include "CTitle.h"
class CMainMenuUI : public CUIElement
{
public:
	CMainMenuUI();
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
private:
};