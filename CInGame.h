#pragma once
#include "CScene.h"
#include "CGrid.h"

class CInGame : public CScene
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;
    
private:
    void MoveFrame();
    CGrid m_grid;
    FRAME m_tFrame;
};