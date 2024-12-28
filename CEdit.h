#pragma once
#include "CScene.h"
class CEdit : public CScene
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
    int m_iWidth;
    int m_iHeight;
};

