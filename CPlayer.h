#pragma once
#include "CGameObject.h"
class CPlayer : public CGameObject
{
public:
    enum STATE { IDLE, WALK, END };
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollision(CGameObject* op) override;
private:
    void KeyInput();
    void ChangeMotion();
    STATE               m_eCurState;
    STATE               m_ePreState;
    ULONG64             m_ullInputDelay;
    ULONG64             m_ullLastInput;

    
};

