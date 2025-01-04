#pragma once
#include "CScene.h"
#include "CGrid.h"
class CTestScene : public CScene
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;    
private:
    void KeyInput();
    CGrid m_grid;
};

