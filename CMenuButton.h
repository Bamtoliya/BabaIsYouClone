#pragma once
#include "CButton.h"
class CMenuButton : public CButton
{
public:
	CMenuButton() {};
	CMenuButton(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
	virtual ~CMenuButton() {};
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
	void OnClick();
private:
	void KeyInput();
};

