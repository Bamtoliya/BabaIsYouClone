#pragma once
#include "CLevel.h"
class CLevel01 : public CLevel
{
public:
    CLevel01() { m_szTitle = L"WHERE DO I GO"; }
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(Graphics* g) override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Restart() override;
private:
    void KeyInput();
    bool m_bTransition;
};

