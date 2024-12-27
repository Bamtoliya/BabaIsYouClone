#pragma once
#include "CGameObject.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static CGameObject* Create()
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CGameObject* Create(float _fX, float _fY, float _fAngle = 0.f)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (0.f != _fAngle)
			pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

