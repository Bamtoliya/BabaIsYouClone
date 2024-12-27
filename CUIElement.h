#pragma once
class CUIElement
{
public:
	virtual void Update() PURE;
	virtual void Render(Graphics* graphic) PURE;

	void UpdateRect();
	void UpdateChild();
	void RenderChild(Graphics* graphic);
	CUIElement* m_parent;
	unordered_map<wstring, CUIElement*> m_child;
	Vector2 m_position;
	Vector2 m_size;
	Rect m_tRect;
	wstring m_text;
	bool m_bFocus;
	bool m_bShow;
	//UIELEMENT m_eID;
	//CUIElement() : m_parent(nullptr), m_position(Vector2_zero), m_size(Vector2_zero), m_text(L""), m_bFocus(false), m_bShow(true), m_eID(UIELEMENT::None) {}
};

