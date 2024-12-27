#pragma once
#include "CGameObject.h"
class CPlayer : public CGameObject
{
public:
    // CGameObject을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Release() override;
private:
    void KeyInput();
    void ChangeMotion();
};

