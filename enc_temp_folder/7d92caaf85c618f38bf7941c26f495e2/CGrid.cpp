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
	CheckWin();
	CheckSentence();
	/*CheckSentenceX();
	CheckSentenceY();*/
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
		if (CheckMove(x, y, index[i].second, index[i].first))
		{
			if (CheckDefeat(x, y, index[i].second, index[i].first))
			{
				wstring t = L"DEFEAT_" + to_wstring((rand() % 5 + 1)) + L".ogg";
				CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
				dynamic_cast<CInGame*>(CSceneManager::GetInstance()->GetCurrentScenePointer())->GetLevel()->Restart();
			}
			else if (CheckPush(x, y, index[i].second, index[i].first))
			{
				cout << "There is PUSH BLOCK\n";
				if (CheckMove(x, y, newX, newY))
				{
					cout << "PUSH BLOCK CAN MOVE\n";
					if (PushBlock(x, y, index[i].second, index[i].first))
					{
						m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
						m_grid[newY][newX]->AddBlock(toMove[i]);
					}
				}
			}
			else 
			{
				wstring t = L"WALK_" + to_wstring((rand() % 5 + 1)) + L".ogg";
				CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
				m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
				m_grid[newY][newX]->AddBlock(toMove[i]);
				//MoveBlock(toMove[i], x, y, newX, newY);
			}
			
		}
	}
}

void CGrid::MoveBlock(CBlock* b, int dx, int dy, int x, int y) 
{
	vector<CBlock*> toMove;
	vector<pair<int, int>> index;
	for (auto& bl : m_grid[y][x]->GetList())
	{
		for (auto& p : bl->GetProperties())
		{
			if (p == PROPERTY::PUSH)
			{
				if ((y + dy >= 0 && y + dy < m_iHeight) && (x + dx >= 0 && x + dx < m_iWidth))
				{
					toMove.push_back(bl);
					index.push_back({ y, x });
				}
			}
		}
	}

	for (int i = 0; i < toMove.size(); ++i) {
		int newX = index[i].second + dx;
		int newY = index[i].first + dy;
		m_grid[index[i].first][index[i].second]->RemoveBlock(toMove[i]);
		m_grid[newY][newX]->AddBlock(toMove[i]);
	}
}

void CGrid::AddBlock(CBlock* b, int x, int y)
{
	m_grid[y][x]->AddBlock(b);
}

void CGrid::Open()
{

}

bool CGrid::CheckPush(int dx, int dy, int x, int y)
{
	if ((y + dy >= 0 && y + dy < m_iHeight) && (x + dx >= 0 && x + dx < m_iWidth))
	{
		for (auto& b : m_grid[y + dy][x + dx]->GetList())
		{
			for (auto& p : b->GetProperties())
			{
				if (p == PROPERTY::PUSH)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CGrid::CheckPushChain(int dx, int dy, int x, int y)
{
	if ((y + dy < 0 || y + dy >= m_iHeight) || (x + dx < 0 || x + dx >= m_iWidth)) {
		return false; // Hit a wall or boundary
	}
	if (!CheckMove(dx, dy, x, y)) {
		return false; // Blocked by a STOP block
	}

	if (CheckPush(dx, dy, x, y)) {
		// Recursive call to check the next block in the chain
		return CheckPushChain(dx, dy, x + dx, y + dy);
	}

	return true;
}

bool CGrid::CheckLastBlockMove(int dx, int dy, int x, int y)
{
	if (!CheckMove(dx, dy, x, y)) {
		return false; // Blocked by a STOP block
	}

	if (CheckPush(dx, dy, x, y)) {
		cout << "How Many Blocks here\n";
		// Recursively check the next block
		return CheckLastBlockMove(dx, dy, x + dx, y + dy);
	}

	// Reached the last block, check if IT can move
	return CheckMove(dx, dy, x, y);
}

bool CGrid::CheckMelt(int dx, int dy, int x, int y)
{
	if ((y + dy >= 0 && y + dy < m_iHeight) && (x + dx >= 0 && x + dx < m_iWidth))
	{
		for (auto& b : m_grid[y + dy][x + dx]->GetList())
		{
			for (auto& p : b->GetProperties())
			{
				if (p == PROPERTY::HOT)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CGrid::CheckDefeat(int dx, int dy, int x, int y)
{
	if ((y + dy >= 0 && y + dy < m_iHeight) && (x + dx >= 0 && x + dx < m_iWidth))
	{
		for (auto& b : m_grid[y + dy][x + dx]->GetList())
		{
			for (auto& p : b->GetProperties())
			{
				if (p == PROPERTY::DEFEAT)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool CGrid::PushBlock(int dx, int dy, int x, int y)
{
	if ((y + dy < 0 || y + dy >= m_iHeight) || (x + dx < 0 || x + dx >= m_iWidth)) return false;

	CBlock* toPush = nullptr;
	for (auto& b : m_grid[y + dy][x + dx]->GetList()) {
		for (auto& p : b->GetProperties()) {
			if (p == PROPERTY::PUSH) {
				toPush = b;
			}
		}
	}

	if (toPush) {
		// 1. Check if the LAST block in the chain can move
		if (CheckLastBlockMove(dx, dy, x + dx, y + dy)) {
			if (PushBlock(dx, dy, x + dx, y + dy))
			{
				// 2. Move the current block
				m_grid[y + dy][x + dx]->RemoveBlock(toPush);
				m_grid[y + dy + dy][x + dx + dx]->AddBlock(toPush);
			}
			// 2. Move the current block
			m_grid[y + dy][x + dx]->RemoveBlock(toPush);
			m_grid[y + dy + dy][x + dx + dx]->AddBlock(toPush);
			return true; // Indicate successful push
		}
		else {
			return false; // Last block cannot move
		}
	}
	return false; // No pushable block found
}

bool CGrid::CheckMove(int dx, int dy, int x, int y)
{
	bool canMove = true;
	if (y + dy >= 0 && y + dy < m_iHeight && x + dx >= 0 && x + dx < m_iWidth)
	{
		for (auto& b : m_grid[y + dy][x + dx]->GetList())
		{
			for (auto& p : b->GetProperties())
			{
				if (p == PROPERTY::STOP)
				{
					canMove = false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return canMove;
}

void CGrid::CheckWin()
{
	vector<CBlock*> you;
	vector<pair<int, int>> youIndex;
	vector<CBlock*> win;
	vector<pair<int, int>> winIndex;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& b : m_grid[i][j]->GetList())
			{
				for (auto& p : b->GetProperties())
				{
					if (p == PROPERTY::YOU)
					{
						you.push_back(b);
						youIndex.push_back({ i, j });
					}
					if (p == PROPERTY::WIN)
					{
						win.push_back(b);
						winIndex.push_back({ i, j });
					}
				}
			}
		}
	}

	for (int i = 0; i < you.size(); ++i)
	{
		for (int j = 0; j < win.size(); ++j)
		{
			if (youIndex[i].first == winIndex[j].first)
			{
				if (youIndex[i].second == winIndex[j].second)
				{
					CSoundManager::GetInstance()->PlaySound(L"TRANSITION_WIN.ogg", CHANNELID::SOUND_EFFECT, 0.8f);
					CSceneManager::GetInstance()->SetStage(nullptr);
				}
			}
		}
	}
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

	vector<vector<CBlock*>> horizontalRules, verticalRules;
	for (int i = 0; i < foundNouns.size(); ++i)
	{
		vector<CBlock*> mayRule;
		int y = index[i].first;
		int x = index[i].second;
		mayRule.push_back(foundNouns[i]);
		if (x + 2 < m_iWidth)
		{
			for (auto& b : m_grid[y][x + 1]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::VERB)
				{
					mayRule.push_back(b);
				}
			}
			for (auto& b : m_grid[y][x + 2]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::NOUN || b->GetBlockType() == BLOCKTYPE::PROPERTY)
				{
					mayRule.push_back(b);
				}
			}
			horizontalRules.push_back(mayRule);
		}


		mayRule.clear();
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
			verticalRules.push_back(mayRule);
		}
	}

	// 가로 규칙 처리
	for (auto& ruleBlocks : horizontalRules)
	{
		if (ruleBlocks.size() == 3)
		{
			CRule tmp;
			tmp.SetSubject(ruleBlocks[0]);
			tmp.SetVerb(ruleBlocks[1]);
			tmp.SetObject(ruleBlocks[2]);
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			tmp.SetIsHorizontal(true);
			tmp.Activate();
			m_rules.emplace(ruleKey, tmp);
			ApplyRule(tmp);
		}
		else
		{
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
				if (it->first.find(ruleKey) != wstring::npos) {
					// it->first 가 ruleKey 를 포함하는 키입니다.
					if (it->second.GetIsHorizontal())
					{
						it->second.InActive();
						ApplyRule(it->second);
						break;
					}
					else {
						continue;
					} // 첫 번째 일치하는 항목만 찾는 경우
				}
			}
		}

	}

	// 세로 규칙 처리
	for (auto& ruleBlocks : verticalRules)
	{
		if (ruleBlocks.size() == 3)
		{
			CRule tmp;
			tmp.SetSubject(ruleBlocks[0]);
			tmp.SetVerb(ruleBlocks[1]);
			tmp.SetObject(ruleBlocks[2]);
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			tmp.SetIsHorizontal(false);
			tmp.Activate();
			m_rules.emplace(ruleKey, tmp);
			ApplyRule(tmp);
		}
		else
		{
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
				if (it->first.find(ruleKey) != wstring::npos) {
					// it->first 가 ruleKey 를 포함하는 키입니다.
					if (!it->second.GetIsHorizontal())
					{
						it->second.InActive();
						ApplyRule(it->second);
						break;
					} else {
						continue;
					}
					; // 첫 번째 일치하는 항목만 찾는 경우
				}
			}
		}
	}
}

void CGrid::CheckSentenceX()
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

	vector<vector<CBlock*>> horizontalRules, verticalRules;
	for (int i = 0; i < foundNouns.size(); ++i)
	{
		vector<CBlock*> mayRule;
		int y = index[i].first;
		int x = index[i].second;
		mayRule.push_back(foundNouns[i]);
		if (x + 2 < m_iWidth)
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
			if (mayRule.size() == 3)
			{
				horizontalRules.push_back(mayRule);
			}
		}
		

		mayRule.clear();
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
			if (mayRule.size() == 3)
			{
				verticalRules.push_back(mayRule);
			}
		}
		
	}

	// 가로 규칙 처리
	for (auto& ruleBlocks : horizontalRules) 
	{
		if (ruleBlocks.size() == 3)
		{
			CRule tmp;
			tmp.SetSubject(ruleBlocks[0]);
			tmp.SetVerb(ruleBlocks[1]);
			tmp.SetObject(ruleBlocks[2]);
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			tmp.SetIsHorizontal(true);
			tmp.Activate();
			m_rules.emplace(ruleKey, tmp);
			ApplyRule(tmp);
		}
		else
		{
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
				if (it->first.find(ruleKey) != wstring::npos) {
					// it->first 가 ruleKey 를 포함하는 키입니다.
					if (it->second.GetIsHorizontal())
					{
						it->second.InActive();
						ApplyRule(it->second);
					}
					break; // 첫 번째 일치하는 항목만 찾는 경우
				}
			}
		}
		
	}

	// 세로 규칙 처리
	for (auto& ruleBlocks : verticalRules) 
	{
		if (ruleBlocks.size() == 3)
		{
			CRule tmp;
			tmp.SetSubject(ruleBlocks[0]);
			tmp.SetVerb(ruleBlocks[1]);
			tmp.SetObject(ruleBlocks[2]);
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			tmp.SetIsHorizontal(false);
			tmp.Activate();
			m_rules.emplace(ruleKey, tmp);
			ApplyRule(tmp);
		}
		else
		{
			wstring ruleKey;
			for (auto& p : ruleBlocks)
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
				if (it->first.find(ruleKey) != wstring::npos) {
					// it->first 가 ruleKey 를 포함하는 키입니다.
					if (!it->second.GetIsHorizontal())
					{
						it->second.InActive();
						ApplyRule(it->second);
					}
					break; // 첫 번째 일치하는 항목만 찾는 경우
				}
			}
		}
	}
}
void CGrid::CheckSentenceY()
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

	vector<vector<CBlock*>> canRule;;
	for (int i = 0; i < foundNouns.size(); ++i)
	{
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
		if (mayRule.size() == 3)
		{
			canRule.push_back(mayRule);
		}
	}

	for (int i = 0; i < canRule.size(); ++i)
	{
		CRule tmp;
		//Simple case
		if (canRule[i].size() == 3)
		{
			tmp.SetSubject(canRule[i][0]);
			tmp.SetVerb(canRule[i][1]);
			tmp.SetObject(canRule[i][2]);
			wstring ruleKey;
			for (auto& p : canRule[i])
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			tmp.Activate();
			m_rules.emplace(ruleKey, tmp);
			ApplyRule(tmp);
		}
		else if(canRule[i].size() < 3)
		{
			wstring ruleKey;
			for (auto& p : canRule[i])
			{
				wstring tmpKey = p->GetImgKey();
				size_t index = tmpKey.find_last_of(L'_');
				wstring parsed = tmpKey.substr(index + 1);
				ruleKey += parsed;
			}
			for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
				if (it->first.find(ruleKey) != wstring::npos) {
					// it->first 가 ruleKey 를 포함하는 키입니다.
					it->second.InActive();
					ApplyRule(it->second);
					break; // 첫 번째 일치하는 항목만 찾는 경우
				}
			}
		}
	}
}

void CGrid::ClearProperties()
{
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			for (auto& b : m_grid[i][j]->GetList())
			{
				if (b->GetBlockType() == BLOCKTYPE::NOUN || b->GetBlockType() == BLOCKTYPE::VERB || b->GetBlockType() == BLOCKTYPE::PROPERTY)
				{

				}
				else
				{
					b->GetProperties().clear();
				}
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

	if (r.IsActve())
	{
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
			r.Activate();
		}
	}
	else
	{
		wstring ruleKey;
		if (r.GetSubjectBlock() != nullptr)
		{
			wstring tmpKey = r.GetSubjectBlock()->GetImgKey();
			size_t index = tmpKey.find_last_of(L'_');
			wstring parsed = tmpKey.substr(index + 1);
			ruleKey += parsed;
		}
		if (r.GetVerbBlock() != nullptr)
		{
			wstring tmpKey = r.GetVerbBlock()->GetImgKey();
			size_t index = tmpKey.find_last_of(L'_');
			wstring parsed = tmpKey.substr(index + 1);
			ruleKey += parsed;
		}
		if (r.GetObjectBlock() != nullptr)
		{
			wstring tmpKey = r.GetObjectBlock()->GetImgKey();
			size_t index = tmpKey.find_last_of(L'_');
			wstring parsed = tmpKey.substr(index + 1);
			ruleKey += parsed;
		}
		wstring tmpKey = r.GetSubjectBlock()->GetImgKey();
		size_t index = tmpKey.find_last_of(L'_');
		wstring parsed = tmpKey.substr(index + 1);
		for (int i = 0; i < target.size(); ++i)
		{
			target[i]->RemoveProperty(StringToProperty(parsed));
		}
		m_rules.erase(ruleKey);
		//m_rules.find(ruleKey)
	}
	
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
		m_ullLastInput = GetTickCount64();
	}
}