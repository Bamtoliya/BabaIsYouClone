#pragma once
#include "CLevel.h"
class CLevel05 : public CLevel
{
public:
    CLevel05() { m_szTitle = L"OFF LIMITS"; }
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

