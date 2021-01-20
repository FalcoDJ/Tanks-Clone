#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include "olcPixelGameEngine.hpp"
#include "FileChecker.hpp"

using namespace olc;

class TankRotations
{
    public:
        static constexpr float North = 6.28318f;
        static constexpr float NorthEast = 0.785398f;
        static constexpr float East = 1.5708f;
        static constexpr float SouthEast = 2.35619f;
        static constexpr float South = 3.14159f;
        static constexpr float SouthWest = 3.92699f;
        static constexpr float West = 4.71239f;
        static constexpr float NorthWest = 5.49779f;
};

class TankEntity
{
protected:
    vf2d m_Pos;
    vf2d m_OldPos;
    float m_Speed; //Speed is in pixels per second
    float m_Radius;

    float MaxDistanceFromOffset = 24;

    bool m_WasShot = true;
    
    float m_Rotation_Of_Body = TankRotations::North;
    float m_Rotation_Of_Turret = TankRotations::North;

    std::string m_PathToSprite;
    Sprite *m_Sprite = nullptr;
    Decal *m_Decal = nullptr;
    Pixel m_Color = WHITE;

    bool m_MovingUp = false;
    bool m_MovingDown = false;
    bool m_MovingLeft = false;
    bool m_MovingRight = false;

    Key m_UpKey;
    Key m_DownKey;
    Key m_LeftKey;
    Key m_RightKey;

public:
    TankEntity(){}
    ~TankEntity(){}

    bool init() 
    {
        bool success = file::doesExist(m_PathToSprite);

        m_Sprite = new Sprite(m_PathToSprite);
        m_Decal = new Decal(m_Sprite);

        return success;
    }

    void spawn(vf2d startingPoint)
    {
        m_WasShot = false;
        m_Pos = startingPoint;
    }

    bool Run(vf2d vMousePos, float fElapsedTime, olc::PixelGameEngine *pge)
    {
        if (!m_WasShot)
        {
            handleInput(pge);
            update(vMousePos, fElapsedTime);
            draw(pge);

            return true;
        }
        else
        {
            return false;
        }
    }

    void update(vf2d vMousePos, float fElapsedTime)
    {
        m_OldPos = m_Pos;

        if (m_MovingLeft)
        {
            m_Pos.x -= m_Speed * fElapsedTime;
            m_OldPos.x += m_Speed * 2 * fElapsedTime;
        }
        if (m_MovingRight)
        {
            m_Pos.x += m_Speed * fElapsedTime;
            m_OldPos.x -= m_Speed * 2 * fElapsedTime;
        }
        if (m_MovingUp)
        {
            m_Pos.y -= m_Speed * fElapsedTime;
            m_OldPos.y += m_Speed * 2 * fElapsedTime;
        }
        if (m_MovingDown)
        {
            m_Pos.y += m_Speed * fElapsedTime;
            m_OldPos.y -= m_Speed * 2 * fElapsedTime;
        }

        m_Rotation_Of_Turret = atan2(vMousePos.y - m_Pos.y, vMousePos.x - m_Pos.x);
        
        if (m_OldPos != m_Pos)
        {
            float desiredRotation = atan2((m_OldPos - m_Pos).norm().y,(m_OldPos - m_Pos).norm().x);
            
            m_Rotation_Of_Body = desiredRotation;
        }
    }

    virtual void handleInput(olc::PixelGameEngine *pge)
    {
        if (pge->GetKey(m_UpKey).bHeld) //Test Up
        {
            m_MovingUp = true;
        }
        else
        {
            m_MovingUp = false;
        }
        if (pge->GetKey(m_DownKey).bHeld) //Test Down
        {
            m_MovingDown = true;
        }
        else
        {
            m_MovingDown = false;
        }
        if (pge->GetKey(m_LeftKey).bHeld) //Test Left
        {
            m_MovingLeft = true;
        }
        else
        {
            m_MovingLeft = false;
        }
        if (pge->GetKey(m_RightKey).bHeld)
        {
            m_MovingRight = true;
        }
        else
        {
            m_MovingRight = false;
        }
    }

    void draw(olc::PixelGameEngine *pge)
    {
        pge->DrawPartialRotatedDecal(m_Pos, m_Decal, m_Rotation_Of_Body, {14,11}, {0,0}, {28,22}, {1,1}, m_Color);
        pge->DrawPartialRotatedDecal(m_Pos, m_Decal, m_Rotation_Of_Turret, {5,11}, {28,0}, {22,22}, {1,1}, m_Color);
    }

    Pixel getColor()
    {
        return m_Color;
    }

    vf2d getPos()
    {
        return m_Pos;
    }
};

#endif