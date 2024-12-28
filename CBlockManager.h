#pragma once
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
	void PickBlock(Point pt, PROPERTY pp);
	void SaveBlock();
	void LoadBlock();
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
	vector<CGameObject*>	m_vecBlock;

	// 판단을 위해서 필요한 정보
	// GAMEWORD, NOUN, VERB, PROPERTY, 
	// 가져와야할 정보
	// 시작X좌표
	// 캐릭터라면 상 하 좌 우 잠 까지
	// 글자라면 고정된 위치 모션은 두개 활성화 비활성화
	// TEXT인지 이미지인지 결정
	// 
	//map < GAMEWORD, TCHAR* pKEY> mapResource;
};

