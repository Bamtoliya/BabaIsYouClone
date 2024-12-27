#pragma once

using namespace FMOD;

enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_ENV, SOUND_END };

class CAudioManager
{
public:
    static CAudioManager* GetInstance() 
    {
        if (!m_pInstance) m_pInstance = new CAudioManager;
        return m_pInstance;
    }
    static void DestroyInstance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
    CAudioManager();
    virtual ~CAudioManager() { Release(); }
    virtual void Initialize();
    virtual void FixedUpdate();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
    virtual void Release();
    void PlayBGM(const TCHAR* pSoundKey, float fVolume);
    void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
    void StopSound(CHANNELID eID);
    void StopAll();
    void SetChannelVolume(CHANNELID eID, float fVolume);

    void LoadAllSounds(const char* path);
private:
    // 사운드 리소스 정보를 갖는 객체 
    static CAudioManager* m_pInstance;
    map<TCHAR*, Sound*> m_mapSound;
    System* m_pSystem;
    Sound* m_pSound;
    Channel* m_channels[SOUND_END];
};

