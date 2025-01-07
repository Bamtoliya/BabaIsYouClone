#pragma once
#include "CBlock.h"
class CCell
{
public:
	CCell() : m_bCanMove(true), m_bCanPush(false) {};
	~CCell() { Release(); }

	void Update();
	void LateUpdate();
	void Render(Graphics* graphic);
	void Render(HDC hDC);
	void Release();
	
	void SetIndex(int _x, int _y) { x = _x, y = _y; }
	void SetXIndex(int _x) { x = _x; }
	void SetYIndex(int _y) { y = _y; }
	int	 GetXIndex() { return x; }
	int	 GetYIndex() { return y; }
	void SetInfo(int x, int y);
	/*void SetIndex(int i) { m_index = i; }
	int GetIndex() { return m_index; }*/

	void AddBlock(CBlock* b);
	void RemoveBlock(CBlock* b);
	void ChangeBlock(CBlock* src);
	list<CBlock*> GetList() { return m_blocks; }
	bool GetCanMove() { return m_bCanMove; }
	bool GetCanPush() { return m_bCanMove; }

private:
	list<CBlock*> m_blocks;
	int x;
	int y;
	INFO m_tInfo;
	bool m_bCanMove;
	bool m_bCanPush;
};

