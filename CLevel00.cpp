#include "pch.h"
#include "Designs.h"
#include "CLevel00.h"

void CLevel00::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_00.dat");
	CSoundManager::GetInstance()->PlayBGM(L"baba.ogg", 0.8f);
	m_color = Color(255, 21, 24, 31);
	m_fTime = 0;
	m_szTitle = L"BABA IS YOU";
	m_bClear = false;
	m_bTransition = false;
}

void CLevel00::Update()
{
	KeyInput();
	m_grid.Update();
	if (m_bTransition) m_fTime += 1.f;
	if (m_bTransition && m_fTime >= 225.f)
	{
		m_bTransition = false, m_fTime = 0.f;
		CSoundManager::GetInstance()->PlaySound(L"TRANSITION_WIN.ogg", CHANNELID::SOUND_EFFECT, 0.8f);
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
	if (m_bClear) m_bTransition = true;
}

void CLevel00::LateUpdate()
{
	m_grid.LateUpdate();
}

void CLevel00::Render(Graphics* g)
{
	//Border
	SolidBrush brush(m_color);
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
	m_grid.Render(g);
	if (m_bTransition)
	{
		WinTransition(g);
	}
}

void CLevel00::Render(HDC hDC)
{
	m_grid.Render(hDC);
}

void CLevel00::Release()
{
}

void CLevel00::Restart()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_00.dat");
	CSoundManager::GetInstance()->PlayBGM(L"baba.ogg", 0.8f);
}

void CLevel00::WinTransition(Graphics* g)
{
	TransitionCloud(g, cosf(DEGTORAD(m_fTime)), m_color);

	if (m_fTime > 135.f && m_fTime < 225.f)
	{
		const TCHAR* sz = L"CONGRATULATION";
		if (sz)
		{
			float startX = OCX / 2 + (-lstrlenW(sz) * 16) / 2;
			float startY = OCY / 2 + (-24) / 2;
			SolidBrush brush(Color(255, 255, 255, 255));
			Image* textImage = CResourceManager::GetInstance()->FindImage(L"TEXT_ALPHABET");
			for (int i = 0; sz[i] != _T('\0'); ++i) {
				Vector2 pos = CResourceManager::GetInstance()->FindText(sz[i]);
				g->DrawImage(textImage, Rect(startX + 16 * i, startY, 24, 24), pos.x, pos.y, 24, 24, UnitPixel);
			}
		}
	}	
}

void CLevel00::KeyInput()
{
	if (KEYIN->KeyDown(VK_ESCAPE))
	{
		CSoundManager::GetInstance()->PlayBGM(L"map.ogg", 0.8f);
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
	if (KEYIN->KeyDown('R'))
	{
		Restart();
	}
}
