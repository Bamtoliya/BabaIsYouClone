#pragma once
#include "CGameObject.h"
class CCollisionManager
{
public:
	static void CollisionRect(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void CollisionRectEx(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static bool CheckRect(CGameObject* _Dst, CGameObject* _Src, float* pX, float* pY);
private:

};

