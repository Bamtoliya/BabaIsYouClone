#pragma once
#include "CScene.h"
class CMenu : public CScene
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Release() override;
    void Render(HDC hDC) override;
private:

};

