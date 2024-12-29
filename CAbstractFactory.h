#pragma once
#include "CGameObject.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};
	static CGameObject* Create()
	{
		CGameObject* pObj = new T();
		pObj->Initialize();
		return pObj;
	}

	static CGameObject* Create(float pX, float pY, float w, float h)
	{
		CGameObject* pObj = new T();
		pObj->Initialize();
		pObj->SetPos(pX, pY);
		pObj->SetSize(w, h);
		return pObj;
	}

	static CGameObject* Create(float _fX, float _fY, float _fAngle = 0.f)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		if (0.f != _fAngle)
			//pObj->SetAngle(_fAngle);
		return pObj;
	}
};

