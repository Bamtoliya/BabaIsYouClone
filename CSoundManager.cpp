#include "pch.h"
#include "CSoundManager.h"
CSoundManager* CSoundManager::m_pInstance = nullptr;

void CSoundManager::PlayBGM(const TCHAR* pSoundKey, float fVolume)
{
	StopSound(CHANNELID::SOUND_BGM);
	auto iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end()) return;
	m_pSystem->playSound(iter->second, nullptr, false, &m_channels[CHANNELID::SOUND_BGM]);
	m_channels[CHANNELID::SOUND_BGM]->setMode(FMOD_LOOP_NORMAL);
	m_channels[CHANNELID::SOUND_BGM]->setLoopCount(-1);
	m_channels[CHANNELID::SOUND_BGM]->setVolume(fVolume);
	m_pSystem->update();
}

void CSoundManager::PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume)
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

void CSoundManager::StopSound(CHANNELID eID)
{
	m_channels[eID]->stop();
}

void CSoundManager::StopAll()
{
}

void CSoundManager::SetChannelVolume(CHANNELID eID, float fVolume)
{
	m_channels[eID]->setVolume(fVolume);
	m_pSystem->update();
}

void CSoundManager::LoadSoundFile(const char* path)
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd;

	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	long handle = _findfirst("../Sound/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "/Sound/";	 // 상대 경로
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		// "../Sound/" + "Success.wav"
		strcat_s(szFullPath, fd.name);
		// "../Sound/Success.wav"

		Sound* pSound = nullptr;

		FMOD_RESULT eRes = m_pSystem->createSound(szFullPath, FMOD_DEFAULT, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	m_pSystem->update();
	_findclose(handle);
}

void CSoundManager::LoadAllSounds(const char* path)
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

void CSoundManager::Release()
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

CSoundManager::CSoundManager()
{
	System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	LoadAllSounds("Assets/Sound/Effect/ToUse");
	LoadAllSounds("Assets/Sound/Music/");
}
