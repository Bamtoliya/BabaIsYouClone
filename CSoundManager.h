#pragma once
using namespace FMOD;
class CSoundManager
{
public:
	static CSoundManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CSoundManager;
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
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
	void LoadSoundFile(const char* path);
	void LoadAllSounds(const char* path);
	void Release();
private:
	CSoundManager();
	~CSoundManager() { Release(); }
	// 사운드 리소스 정보를 갖는 객체 
	static CSoundManager* m_pInstance;
	map<TCHAR*, Sound*> m_mapSound;
	System* m_pSystem;
	Sound* m_pSound;
	Channel* m_channels[CHANNELID::SOUND_END];
};

