#include "pch.h"
#include "CPlayer.h"
#include "Designs.h"

void CPlayer::Initialize()
{
    m_tInfo = { 0, 0, 48.f, 48.f };
    m_fSpeed = 0.f;

    m_eCurState = IDLE;
    m_ePreState = IDLE;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 2;
    m_tFrame.iMotion = 0;
    m_tFrame.ullSpeed = 200;
    m_tFrame.ullTime = GetTickCount64();

    m_ullInputDelay = 50;
    m_ullLastInput = 0;
}

void CPlayer::Update()
{
    KeyInput();
    ChangeMotion();
    __super::UpdateRect();
}

void CPlayer::LateUpdate()
{
    __super::MoveFrame();
}

void CPlayer::Render(Graphics* graphic)
{
    SolidBrush brush(Color::Red);
    Image* image = CResourceManager::GetInstance()->FindImage(L"Character");
    int startX = 0;
    switch (m_eDir)
    {
    case DIRECTION::LEFT:
        startX = 776;
        break;
    case DIRECTION::RIGHT:
        startX = 576;
        break;
    case DIRECTION::UP:
        startX = 676;
        break;
    case DIRECTION::DOWN:
        startX = 876;
        break;
    default:
        break;
    }

    graphic->DrawImage(image, m_tRect, startX + m_tFrame.iFrameAnimation * 25, 1 + m_tFrame.iFrameStart * 25, 23, 24, UnitPixel);
    if (g_bDevmode)
    {
        Pen pen(Color::Green);
        graphic->DrawRectangle(&pen, m_tRect);
    }
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
    if (m_ullLastInput + m_ullInputDelay < GetTickCount64())
    {
        if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
        {
            m_tInfo.fX -= TILECX;
            m_eCurState = STATE::WALK;
            m_eDir = DIRECTION::LEFT;
            ++m_tFrame.iFrameAnimation;
        }
        else if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
        {
            m_tInfo.fX += TILECX;
            m_eCurState = STATE::WALK;
            m_eDir = DIRECTION::RIGHT;
            ++m_tFrame.iFrameAnimation;
        }
        else if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
        {
            m_tInfo.fY -= TILECY;
            m_eCurState = STATE::WALK;
            m_eDir = DIRECTION::UP;
            ++m_tFrame.iFrameAnimation;
        }
        else if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
        {
            m_tInfo.fY += TILECY;
            m_eCurState = STATE::WALK;
            m_eDir = DIRECTION::DOWN;
            ++m_tFrame.iFrameAnimation;
        }
        if (m_tFrame.iFrameAnimation > 3)
            m_tFrame.iFrameAnimation = 0;
        
        m_ullLastInput = GetTickCount64();
    }
    
}

void CPlayer::ChangeMotion()
{
    
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case CPlayer::IDLE:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.ullSpeed = 200;
            m_tFrame.ullTime = GetTickCount64();
            break;
        case CPlayer::WALK:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 2;
            m_tFrame.iMotion = 1;
            m_tFrame.ullSpeed = 200;
            m_tFrame.ullTime = GetTickCount64();
            break;
        case CPlayer::END:
            break;
        default:
            break;
        }
        m_ePreState = m_eCurState;
    }
}

void CPlayer::Render(HDC hDC)
{
}

void CPlayer::OnCollision(CGameObject* op)
{
    //m_tInfo.fX -= TILECX;
}
