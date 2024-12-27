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
	virtual void Release() PURE;

	INFO		GetInfo() { return m_tInfo; }
	const INFO* GetInfoPointer() { return &m_tInfo; }
	const Rect* GetRect() { return &m_tRect; }

	void		SetPos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		SetPosX(float _fX) { m_tInfo.fX += _fX; }
	void		SetPosY(float _fY) { m_tInfo.fY += _fY; }
	bool		GetDead() { return m_bDead; }
	void		SetDead() { m_bDead = true; }
	void		SetImgKey(const TCHAR* pImgKey) { m_pImgKey = pImgKey; }

	//void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	
	
	//void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	//void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	

	

	void UpdateRect();
	void MoveFrame();
protected:
	INFO		m_tInfo;
	Rect		m_tRect;
	FRAME		m_tFrame;
	float		m_fSpeed;

	bool		m_bDead;
	bool		m_bActive;

	const TCHAR* m_pImgKey;
	CGameObject* m_pTarget;
	/*DIRECTION	m_eDir;
	RENDERID	m_eRender;*/
};

