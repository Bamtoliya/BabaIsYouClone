#pragma once
class CUIElement
{
public:
	CUIElement() : m_parent(nullptr), m_text(L"PlaceHolder"), m_bActive(true), m_bFocus(false), m_bShow(true), m_eID(UITYPE::None), m_pImage(nullptr)
	{
		ZeroMemory(&m_tInfo, sizeof(INFO));
		ZeroMemory(&m_tRect, sizeof(Rect));
	}
    CUIElement(CUIElement* m_parent, const vector<CUIElement*>& m_child, const INFO& m_tInfo, const Rect& m_tRect, const TCHAR*& m_text, bool m_bActive, bool m_bFocus, bool m_bShow, const UITYPE& m_eID, Image* m_pImage)
		: m_parent(m_parent), m_child(m_child), m_tInfo(m_tInfo), m_tRect(m_tRect), m_text(m_text), m_bActive(m_bActive), m_bFocus(m_bFocus), m_bShow(m_bShow), m_eID(m_eID), m_pImage(m_pImage)
	{
	}
	virtual void Update() PURE;
	virtual void Render(Graphics* graphic) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void UpdateChild();
	virtual void UpdateRect();
	virtual void RenderChild(Graphics* graphic);
	virtual void RenderChild(HDC hDC);

	CUIElement* GetParent() { return m_parent; }
	void SetParent(CUIElement* p) { m_parent = p; }

	vector<CUIElement*> GetChilds() { return m_child; }
	void AddChild(CUIElement* c) { m_child.emplace_back(c); }
	//void AddChild(const TCHAR* sz, CUIElement* c) { m_child.emplace(c); }

	INFO GetInfo() { return m_tInfo; }
	const INFO* GetInfoPointer() { return &m_tInfo; }
	void SetInfo(INFO info) { m_tInfo = info; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetPosX(float fX) { m_tInfo.fX = fX; }
	void SetPosY(float fY) { m_tInfo.fY = fY; }
	void SetSize(float w, float h) { m_tInfo.fCX = w, m_tInfo.fCY = h; }

	const Rect* GetRect() { return &m_tRect; }

	void Show() { m_bShow = true; }
	void Hide() { m_bShow = false; }

	void SetFocus(bool f) { m_bFocus = f; }

	bool IsActive() { return m_bActive; }
	bool IsFocus() { return m_bFocus; }
	bool IsShow() { return m_bShow; }

	UITYPE GetUIType() { return m_eID; }
	const TCHAR* GetText() { return m_text; }

	void Dump()
	{
		printf("INFO: %0.f,	%0.f,	%0.f,	%0.f\n", m_tInfo.fX, m_tInfo.fY, m_tInfo.fX, m_tInfo.fY);
		printf("Rect: %d,	%d,	%d,	%d\n", m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height);
		printf("TEXT: %ls\n", m_text);
	}

protected:
	
	CUIElement* m_parent;
	vector<CUIElement*> m_child;
	INFO m_tInfo;
	Rect m_tRect;
	const TCHAR* m_text;
	bool m_bActive;
	bool m_bFocus;
	bool m_bShow;
	UITYPE m_eID;
	Image* m_pImage;
};

