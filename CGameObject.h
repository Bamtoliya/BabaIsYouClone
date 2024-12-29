#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject() {};
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(Graphics* graphic) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

	INFO		GetInfo() { return m_tInfo; }
	const INFO* GetInfoPointer() { return &m_tInfo; }
	const Rect* GetRect() { return &m_tRect; }

	void		SetPos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		SetSize(float w, float h)
	{
		m_tInfo.fCX = w;
		m_tInfo.fCY = h;
	}

	void		SetPosX(float _fX) { m_tInfo.fX += _fX; }
	void		SetPosY(float _fY) { m_tInfo.fY += _fY; }
	bool		GetDead() { return m_bDead; }
	void		SetDead() { m_bDead = true; }
	void		SetImgKey(const TCHAR* pImgKey) { m_pImgKey = pImgKey; }
	void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }

	virtual void OnCollision(CGameObject* op) PURE;
	DIRECTION GetDIRECTION() { return m_eDir; }
	
	//void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	//void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void UpdateRect();
	void MoveFrame();
protected:
	INFO			m_tInfo;
	Rect			m_tRect;
	FRAME			m_tFrame;
	DIRECTION		m_eDir;
	float			m_fSpeed;
	bool			m_bAnimate;
	bool			m_bDead;
	bool			m_bActive;
	const TCHAR*	m_pImgKey;
	CGameObject*	m_pTarget;
};

