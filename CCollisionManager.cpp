#include "pch.h"
#include "CCollisionManager.h"

void CCollisionManager::CollisionRect(list<CGameObject*> _Dst, list<CGameObject*> _Src)
{
	Rect rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if(Dst->GetRect()->IntersectsWith(*Src->GetRect()))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
		}
	}
}

void CCollisionManager::CollisionRectEx(list<CGameObject*> _Dst, list<CGameObject*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckRect(Dst, Src, &fX, &fY))
			{
				// 상 하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->GetInfo().fY < Src->GetInfo().fY)
					{
						Dst->SetPosY(-fY);
					}
					// 하 충돌
					else
					{
						Dst->SetPosY(+fY);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->GetInfo().fX < Src->GetInfo().fX)
					{
						Dst->SetPosX(-fX);
					}
					// 우 충돌
					else
					{
						Dst->SetPosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionManager::CheckRect(CGameObject* _Dst, CGameObject* _Src, float* pX, float* pY)
{
	float		fX = abs(_Dst->GetInfo().fX - _Src->GetInfo().fX);
	float		fY = abs(_Dst->GetInfo().fY - _Src->GetInfo().fY);

	float		fRadiusX = (_Dst->GetInfo().fCX + _Src->GetInfo().fCX) * 0.5f;
	float		fRadiusY = (_Dst->GetInfo().fCY + _Src->GetInfo().fCY) * 0.5f;

	if ((fRadiusX >= fX) && (fRadiusY >= fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;
		return true;
	}

	return false;
}
