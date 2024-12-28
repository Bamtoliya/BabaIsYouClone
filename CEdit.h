#pragma once
#include "CScene.h"
class CEdit : public CScene
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Release() override;
private:
    void KeyInput();

    // CScene을(를) 통해 상속됨
    void Render(HDC hDC) override;
};

