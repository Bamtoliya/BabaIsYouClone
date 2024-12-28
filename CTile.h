#pragma once
#include "CGameObject.h"
class CTile : public CGameObject
{
public:
    CTile();
    virtual ~CTile();
    int			GetDrawID() { return m_iDrawID; }
    int			GetOption() { return m_iOption; }

    void		SetDrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
    void		SetOption(int _iOption) { m_iOption = _iOption; }
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* graphic) override;
    void Release() override;
private:
    int		m_iDrawID;
    int		m_iOption;

    // CGameObject을(를) 통해 상속됨
    void OnCollision(CGameObject* op) override;
};

