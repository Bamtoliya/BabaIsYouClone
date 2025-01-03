#pragma once
#include "CGrid.h"
#include "CBlock.h"
class CBlockManager
{
public:
	
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(Graphics* g);
	void Render(HDC hDC);
	void Release();
	void PickBlock(Point pt, CBlock b);
	void SaveBlock();
	void LoadBlock();
	void LoadBlock(const TCHAR* filepath);
	void LoadBlock(CGrid& dst, const TCHAR* filepath);
	void SetWidth(int w) { m_iWidth = w; }
	void SetHeight(int h) { m_iHeight = h; }
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	
	static CBlockManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBlockManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CBlockManager();
	~CBlockManager() { Release(); }
	static CBlockManager* m_pInstance;
	CGrid m_levelGrid;
	int m_iWidth;
	int m_iHeight;
};

