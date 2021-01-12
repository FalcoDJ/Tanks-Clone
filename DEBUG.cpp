//Definitions of Debug Functions

#include "Tanks.hpp"

void Tanks::DebugCreate()
{
    std::cout << "Debuging Enabled!" << std::endl;
}

void Tanks::DebugUpdate(float fElapsedTime)
{
    FrameCounter++;
}

void Tanks::DebugDraw(olc::PixelGameEngine *pge)
{
    pge->DrawStringDecal({5,5}, "Frame Counter: " + std::to_string(FrameCounter), olc::YELLOW);
    pge->DrawStringDecal({5,15}, "FPS: " + std::to_string(GetFPS()), olc::YELLOW);
}

void Tanks::DebugDestroy()
{
    std::cout << "Debugged Successfully!" << std::endl;
}
