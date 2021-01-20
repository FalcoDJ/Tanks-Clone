#pragma once

#include "TankEntity.hpp"

class Player : public TankEntity
{
public:
    Player()
    {
        m_PathToSprite = "Tank-Player.png";
        m_Color = CYAN;

        m_UpKey = olc::Key::W;
        m_DownKey = olc::Key::S;
        m_LeftKey = olc::Key::A;
        m_RightKey = olc::Key::D;

        m_Speed = 40;
        m_Radius = 11;
    }
    ~Player(){}
};