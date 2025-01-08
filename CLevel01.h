#pragma once
#include "CLevel.h"
class CLevel01 : public CLevel
{
public:
    CLevel01() { m_szTitle = L"LAVA IS DEFEAT"; }
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(Graphics* g) override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Restart() override;
private:
    void KeyInput();
    Color m_color;
    float m_fTime;
    bool m_bTransition;
};

