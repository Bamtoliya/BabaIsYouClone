#pragma once
#include "CUIElement.h"
class CButton : public CUIElement
{
public:
	CButton() {};
	CButton(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
	virtual ~CButton() {};
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
	void OnClick();
private:
	void KeyInput();
};

