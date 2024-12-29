#pragma once
#include "CButton.h"
#include "Blocks.h"
class CBlockButton : public CButton
{
public:
	CBlockButton();
	virtual ~CBlockButton() {};
	CBlockButton(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show);
	CBlockButton(float fX, float fY, float w, float h, const TCHAR* sz, BLOCKTYPE type, CUIElement* parent, bool show);
	void Update() override;
	void Render(Graphics* graphic) override;
	void Render(HDC hDC) override;
private:
	void KeyInput();
	void OnClick();
	CBlock* m_target;
};

