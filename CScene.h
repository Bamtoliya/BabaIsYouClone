#pragma once
class CScene
{
public:
	CScene() {}
	virtual ~CScene() {}
	virtual void Initialize()	PURE;
	virtual void FixedUpdate()	PURE;
	virtual void Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(Graphics* g)		PURE;
	virtual void Release()		PURE;
};

