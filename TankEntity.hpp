#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include "olcPixelGameEngine.hpp"

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
    float m_Rotation_Of_Body = TankRotations::North;
    float m_Rotation_Of_Turret = TankRotations::North;
    std::string m_PathToSprite;
    
public:
    TankEntity(){}
    ~TankEntity(){}

    bool init() 
    {
        return true;
    }

    void update(float fElapsedTime)
    {

    }

    void draw(olc::PixelGameEngine *pge)
    {
        
    }
};

#endif