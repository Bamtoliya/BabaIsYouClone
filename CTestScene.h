#pragma once
#include "CScene.h"
class CTestScene : public CScene
{
public:
    void Initialize() override;
    void FixedUpdate() override;
    void Update() override;
    void LateUpdate() override;
    void Render(Graphics* g) override;
    void Release() override;
};

