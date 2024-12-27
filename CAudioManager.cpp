#include "pch.h"
#include "CAudioManager.h"

CAudioManager* CAudioManager::m_pInstance = nullptr;

CAudioManager::CAudioManager()
{
	System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	//LoadAllSounds(SOUNDPATH);
}

void CAudioManager::Initialize()
{
	if (!m_pSystem)
	{
		System_Create(&m_pSystem);
		m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	}
	//LoadAllSounds(SOUNDPATH);
}

void CAudioManager::FixedUpdate()
{
}

void CAudioManager::Update()
{

}

void CAudioManager::LateUpdate()
{
}

void CAudioManager::Render()
{
}

void CAudioManager::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		Mypair.second->release();
	}
	m_mapSound.clear();

	m_pSystem->release();
	m_pSystem->close();
}

void CAudioManager::PlayBGM(const TCHAR* pSoundKey, float fVolume)
{
	auto iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end()) return;
	m_pSystem->playSound(iter->second, nullptr, false, &m_channels[SOUND_BGM]);
	m_channels[SOUND_BGM]->setMode(FMOD_LOOP_NORMAL);
	m_channels[SOUND_BGM]->setLoopCount(-1);
	m_channels[SOUND_BGM]->setVolume(fVolume);
	m_pSystem->update();
}

void CAudioManager::PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume)
{
	auto iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end()) return;
	bool isPlaying;
	m_channels[eID]->isPlaying(&isPlaying);
	if (isPlaying)
	{
		m_pSystem->playSound(iter->second, NULL, false, &m_channels[eID]);
	}
	else
	{
		m_pSystem->playSound(iter->second, NULL, false, &m_channels[eID]);
	}

	m_channels[eID]->setVolume(fVolume);

	m_pSystem->update();
}

void CAudioManager::StopSound(CHANNELID eID)
{
	m_channels[eID]->stop();
}

void CAudioManager::StopAll()
{
	for (size_t i = 0; i < SOUND_END; ++i)
		m_channels[i]->stop();
}

void CAudioManager::SetChannelVolume(CHANNELID eID, float fVolume)
{
	m_channels[eID]->setVolume(fVolume);
	m_pSystem->update();
}

void CAudioManager::LoadAllSounds(const char* path)
{
	char search_path[260];
	struct _finddata_t fd;
	intptr_t handle;

	// 현재 디렉토리에서 모든 파일 및 디렉토리 검색
	sprintf_s(search_path, "%s/*.*", path);
	handle = _findfirst(search_path, &fd);

	if (handle != -1L) {
		do {
			// "."과 ".." 디렉토리는 무시
			if (strcmp(fd.name, ".") == 0 || strcmp(fd.name, "..") == 0)
				continue;

			// 파일 경로 생성
			sprintf_s(search_path, "%s/%s/", path, fd.name);

			// 디렉토리인 경우 재귀적으로 호출
			if (fd.attrib & _A_SUBDIR) {
				LoadAllSounds(search_path);
			}
			else {
				// 파일인 경우 처리
				char szFullPath[128] = "";
				strcpy_s(szFullPath, path);  // 상대 경로3
				strcat_s(szFullPath, fd.name);

				Sound* pSound = nullptr;
				FMOD_RESULT eRes = m_pSystem->createSound(szFullPath, FMOD_DEFAULT, 0, &pSound);
				if (eRes == FMOD_OK) {
					int iLength = strlen(fd.name) + 1;
					TCHAR* pSoundKey = new TCHAR[iLength];
					ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
					MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);
					m_mapSound.emplace(pSoundKey, pSound);
				}
			}
		} while (_findnext(handle, &fd) == 0);
		_findclose(handle);
	}
}
