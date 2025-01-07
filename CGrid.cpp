#include "pch.h"
#include "CGrid.h"
#include "Designs.h"
#include "CLevelBlock.h"

CGrid::CGrid() : m_iWidth(33), m_iHeight(18), m_vCenter(OCX / 2, OCY / 2)
{
	
	m_grid = vector<vector<CCell*>>(m_iHeight, vector<CCell*>(m_iWidth));
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	m_tRect = { startX, startY, TILECX * m_iWidth, TILECY * m_iHeight };
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j] = new CCell();
			m_grid[i][j]->SetInfo(startX + j * TILECX, startY + i * TILECY);
			m_grid[i][j]->SetIndex(i, j);
			m_grid[i][j]->AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"", BLOCKTYPE::NONE));
		}
	}
	m_ullDelay = 200;
	m_ullLastInput = GetTickCount64();
}

void CGrid::Initialize()
{
	m_grid = vector<vector<CCell*>>(m_iHeight, vector<CCell*>(m_iWidth));
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	m_tRect = { startX, startY, TILECX * m_iWidth, TILECY * m_iHeight };
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j] = new CCell();
			m_grid[i][j]->SetInfo(startX + j * TILECX, startY + i * TILECY);
			m_grid[i][j]->SetIndex(i, j);
			m_grid[i][j]->AddBlock(new CBlock(startX + j * TILECX, startY + i * TILECY, L"", BLOCKTYPE::NONE));
		}
	}
}

void CGrid::Update()
{
	KeyInput();
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j]->Update();
		}
	}
	CheckSentence();
}

void CGrid::LateUpdate()
{
	for (int i = 0; i < m_iHeight; ++i)
	{	
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j]->LateUpdate();
		}
	}
}

void CGrid::Render(Graphics* g)
{
	int startX = m_vCenter.x - TILECX * m_iWidth / 2.f;
	int startY = m_vCenter.y - TILECY * m_iHeight / 2.f;
	int endX = m_vCenter.x + TILECX * m_iWidth / 2.f;
	int endY = m_vCenter.y + TILECY * m_iHeight / 2.f;
#pragma region 그리드 표현
	Pen pen(Color(125, 0, 255, 0), 1);
	if (g_bDevmode)
	{
		//세로선
		for (int i = 0; i <= m_iWidth; ++i)
		{
			g->DrawLine(&pen, Point(startX + i * TILECX, startY), Point(startX + i * TILECX, endY));
		}
		//가로선
		for (int i = 0; i <= m_iHeight; ++i)
		{
			g->DrawLine(&pen, Point(startX, startY + i * TILECY), Point(endX, startY + i * TILECY));
		}
	}
#pragma endregion

	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			m_grid[i][j]->Render(g);
		}
	}
}

void CGrid::Render(HDC hDC)
{
}

void CGrid::Move(int x, int y)
{
	vector<CBlock*> toMove;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				for (auto& p : t->GetProperties())
				{
					if (p == PROPERTY::YOU)
					{
						if ((i + y >= 0 && i + y < m_iHeight) && (j + x >= 0 && j + x < m_iWidth))
						{
							toMove.push_back(t);
							index.push_back({ i, j });
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < toMove.size(); ++i) {
		int newX = index[i].second + x;
		int newY = index[i].first + y;
		MoveBlock(toMove[i], newX, newY);
	}
}

void CGrid::MoveBlock(CBlock* b, int x, int y)
{
	for (auto& b : m_grid[y][x]->GetList())
	{
		//CheckBoundary and Recursively call the 
		if (b->GetBlockType() == BLOCKTYPE::NOUN || b->GetBlockType() == BLOCKTYPE::VERB || b->GetBlockType() == BLOCKTYPE::PROPERTY)
		{
			
		}
	}
	
	vector<CBlock*> toMove;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == b)
				{

					if ((i + y >= 0 && i + y < m_iHeight) && (j + x >= 0 && j + x < m_iWidth))
					{
						toMove.push_back(t);
						index.push_back({ i, j });
					}
				}
			}
		}
	}
	for (int i = 0; i < toMove.size(); ++i) {
		int newX = index[i].second + x;
		int newY = index[i].first + y;

		// Check if the new position is within the grid bounds
		if ((newY >= 0 && newY < m_iHeight) && (newX >= 0 && newX < m_iWidth)) {
			// Check for collision in the destination cell
			if (m_grid[newY][newX]->GetList().size() > 0) {
				CBlock* blockingBlock = m_grid[newY][newX]->GetList().front();

				// Check the blocking block's properties to determine if it can be pushed
				bool canPush = false;
				set<PROPERTY> properties = blockingBlock->GetProperties();
				if (properties.find(PROPERTY::PUSH) != properties.end()) { // Assuming you have a PUSHABLE property
					canPush = true;
				}

				if (canPush) {
					// Recursively move the blocking block
					MoveBlock(blockingBlock, x, y);

					// Check if the blocking block actually moved 
					// (it might have been blocked by something else)
					bool didMove = false;
					for (auto& block : m_grid[newY][newX]->GetList()) {
						if (block == blockingBlock) {
							didMove = true;
							break;
						}
					}

					// Only move the original block if the blocking block was successfully pushed
					if (didMove) {
						m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
						m_grid[newY][newX]->AddBlock(toMove[i]);
					}
				} // else: the block cannot be pushed, so the original block also stops
			}
			else {
				// No collision, move the block normally
				m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
				m_grid[newY][newX]->AddBlock(toMove[i]);
			}
		}
	}
}

void CGrid::AddBlock(CBlock* b, int x, int y)
{
	m_grid[y][x]->AddBlock(b);
}

void CGrid::Open()
{

}

void CGrid::CheckSentence()
{
	vector<CBlock*> foundNouns;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t->GetBlockType() == BLOCKTYPE::NOUN)
				{
					foundNouns.push_back(t);
					index.push_back({ i, j });
				}
			}
		}
	}

	for (int i = 0; i < foundNouns.size(); ++i)
	{
		CRule tmp;
		vector<CBlock*> mayRule;
		int y = index[i].first;
		int x = index[i].second;
		mayRule.push_back(foundNouns[i]);
		if (y + 2 < m_iHeight)
		{
			for (auto& b : m_grid[y + 1][x]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::VERB)
				{
					mayRule.push_back(b);
				}
			}
			for (auto& b : m_grid[y + 2][x]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::NOUN || b->GetBlockType() == BLOCKTYPE::PROPERTY)
				{
					mayRule.push_back(b);
				}
			}
		}

		//Simple case
		if (mayRule.size() == 3)
		{
			tmp.SetSubject(mayRule[0]);
			tmp.SetVerb(mayRule[1]);
			tmp.SetObject(mayRule[2]);
			ApplyRule(tmp);
			mayRule.pop_back();
			mayRule.pop_back();
		}
		else
		{
			for (auto& b : mayRule)
			{
				b->InActive();
			}
		}
		if (x + 2 < m_iHeight)
		{
			for (auto& b : m_grid[y][x+1]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::VERB)
				{
					mayRule.push_back(b);
				}
			}
			for (auto& b : m_grid[y][x+2]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::NOUN || b->GetBlockType() == BLOCKTYPE::PROPERTY)
				{
					mayRule.push_back(b);
				}
			}
		}
		if (mayRule.size() == 3)
		{
			tmp.SetSubject(mayRule[0]);
			tmp.SetVerb(mayRule[1]);
			tmp.SetObject(mayRule[2]);
			ApplyRule(tmp);
		}
		else
		{
			for (auto& b : mayRule)
			{
				b->InActive();
			}
		}
	}
}

void CGrid::CheckTileNeighbor()
{
	vector<CBlock*> toCheck;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t->GetBlockType() == BLOCKTYPE::TILE)
				{
					toCheck.push_back(t);
					/*if ((i + y >= 0 && i + y < m_iHeight) && (j + x >= 0 && j + x < m_iWidth))
					{
						toCheck.push_back(t);
						index.push_back({ i, j });

					}*/
				}
			}
		}
	}
}

void CGrid::EnterLevel(CBlock* cursor)
{
	list<CBlock*> findLevel;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == cursor)
				{
					findLevel = m_grid[i][j]->GetList();
				}
			}
		}
	}

	for (auto& l : findLevel)
	{
		if (l->GetBlockType() == BLOCKTYPE::LEVEL)
		{
			dynamic_cast<CLevelBlock*>(l)->Enter();
		}
	}
}

void CGrid::EditBlock(CBlock b, int x, int y)
{
	m_grid[y][x]->GetList().back()->SetImgKey(b.GetImgKey());
	m_grid[y][x]->GetList().back()->SetBlockType(b.GetBlockType());
}

void CGrid::PrintLevel(CBlock* cursor, Graphics* g, int x, int y)
{
	list<CBlock*> findLevel;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == cursor)
				{
					findLevel = m_grid[i][j]->GetList();
				}
			}
		}
	}

	for (auto& l : findLevel)
	{
		if (l->GetBlockType() == BLOCKTYPE::LEVEL)
		{
			const TCHAR* sz = dynamic_cast<CLevelBlock*>(l)->GetTitle();
			if (sz)
			{
				float startX;
				float startY;
				if (x != 0 && y != 0)
				{
					startX = x + (- lstrlenW(sz) * 16) / 2;
					startY = y + (- 24) / 2;
				}
				else
				{
					startX = x;
					startY = y;
				}
				
				SolidBrush brush(Color(255, 255, 255, 255));
				Image* textImage = CResourceManager::GetInstance()->FindImage(L"TEXT_ALPHABET");
				for (int i = 0; sz[i] != _T('\0'); ++i) {
					Vector2 pos = CResourceManager::GetInstance()->FindText(sz[i]);
					g->DrawImage(textImage, Rect(startX + 16 * i, startY, 24, 24), pos.x, pos.y, 24, 24, UnitPixel);
				}
			}
		}
	}
}

bool CGrid::CheckCanMove(DIRECTION d, int x, int y)
{
	switch (d)
	{
	case DIRECTION::NONE:
		break;
	case DIRECTION::LEFT:
		break;
	case DIRECTION::RIGHT:
		break;
	case DIRECTION::UP:
		break;
	case DIRECTION::DOWN:
		break;
	default:
		break;
	}
	//m_grid[y][x].
	return false;
}

void CGrid::ApplyRule(CRule& r)
{
	vector<CBlock*> target;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (_tcsstr(t->GetImgKey(), r.GetSubjectBlock()->GetImgKey()) != NULL)
				{
					if (t->GetBlockType() != BLOCKTYPE::NOUN)
					{
						target.push_back(t);
					}
				}
			}
		}
	}

	if (_tcsstr(r.GetVerbBlock()->GetImgKey(), L"IS") != NULL)
	{
		for (int i = 0; i < target.size(); ++i)
		{
			if (_tcsstr(r.GetObjectBlock()->GetImgKey(), L"NOUN") != NULL)
			{
				target[i]->Apply(r.GetObjectBlock());
			}
			else if (_tcsstr(r.GetObjectBlock()->GetImgKey(), L"PROPERTY") != NULL)
			{
				wstring tmp = r.GetObjectBlock()->GetImgKey();
				size_t index = tmp.find_last_of(L'_');
				wstring parsed = tmp.substr(index + 1);
				target[i]->AddProperty(StringToProperty(parsed));
			}
		}
	}
	r.GetSubjectBlock()->Activate();
	r.GetObjectBlock()->Activate();
	r.GetVerbBlock()->Activate();
}

void CGrid::MoveCursor(CBlock* cursor, int x, int y)
{
	vector<CBlock*> toMove;
	vector<pair<int, int>> index;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& t : m_grid[i][j]->GetList())
			{
				if (t == cursor)
				{
					if ((i + y >= 0 && i + y < m_iHeight) && (j + x >= 0 && j + x < m_iWidth))
					{
						toMove.push_back(t);
						index.push_back({ i, j });
					}
				}
			}
		}
	}

	for (int i = 0; i < toMove.size(); ++i) {
		int newX = index[i].second + x;
		int newY = index[i].first + y;
		m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
		m_grid[newY][newX]->AddBlock(toMove[i]);
	}
}

void CGrid::KeyInput()
{
	if (m_ullLastInput + m_ullDelay < GetTickCount64())
	{
		if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
		{
			Move(-1, 0);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		{
			Move(1, 0);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
		{
			Move(0, -1);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
		{
			Move(0, 1);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_ESCAPE))
		{
			//m_grid.EnterLevel(m_Cursor);
		}
		m_ullLastInput = GetTickCount64();
	}
}