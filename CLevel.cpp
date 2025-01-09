#include "pch.h"
#include "CLevel.h"
#include "Designs.h"

void CLevel::SaveMove()
{
	CGrid gridCopy = m_grid;
	m_undo.push(gridCopy);
}

void CLevel::Undo()
{
	if (!m_undo.empty())
	{
		wstring t = L"UNDO_" + to_wstring((rand() % 5 + 1)) + L".ogg";
		CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
		m_grid.CopyGrid(m_undo.top(), m_grid);
		m_undo.pop();
	}
}

void CLevel::WinTransition(Graphics* g)
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
