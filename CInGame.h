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
    
private:
    CWorldMap* m_WorldMap;
    CLevel* m_curLevel;
    bool m_bLevel;
    bool m_bWorld;
};