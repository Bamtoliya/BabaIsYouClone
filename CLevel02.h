#pragma once
#include "CLevel.h"
class CLevel02 : public CLevel
{
public:
    CLevel02() { m_szTitle = L"NOW WHAT IS THIS"; }
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

