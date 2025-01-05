#pragma once
#include "CScene.h"
#include "CGrid.h"
#include "CWorldMap.h"
#include "CLevel.h"

class CInGame : public CScene
{
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Render(HDC hDC) override;
    void Release() override;
    void SetInLevel(bool l) { m_bLevel = l; }
    void SetInWorld(bool w) { m_bWorld = w; }
    bool GetInLevel() { return m_bLevel; }
    bool GetInWorld() { return m_bWorld; }
    void SetLevel(CLevel* level);
    CLevel* GetLevel() { return m_curLevel; }
    void EnterTransition(Graphics* g);
    void WinTransition(Graphics* g);
    void ReturnTransition(Graphics* g);
private:
    CWorldMap* m_WorldMap;
    CLevel* m_curLevel;
    bool m_bLevel;
    bool m_bWorld;
    ULONG64 m_ullTransitionTime;
    ULONG64 m_ullTransitionDelay;
    float m_fTransitionTime;
    Rect m_tRect1;
    Rect m_tRect2;
    Rect m_tRect3;
    Rect m_tRect4;
};