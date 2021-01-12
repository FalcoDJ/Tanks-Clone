#ifndef TANKS_ENGINE_HPP
#define TANKS_ENGINE_HPP

#include "olcPixelGameEngine.hpp"
#include "PGE_intro.hpp"
#include "TankEntity.hpp"

using namespace olc;

class Tanks : public PixelGameEngine
{
private: //Debug Functions and Vars
    void DebugCreate();
    void DebugUpdate(float fElapsedTime);
    void DebugDraw(olc::PixelGameEngine *pge);
    void DebugDestroy();

    int FrameCounter = 0;

private:
    PGE_INTRO csPGE2_logo;

    TankEntity tTank;
public:
    Tanks()
    {
        sAppName = "Tanks!";
    }
    ~Tanks(){}
    vf2d ScreenSize = {512,288};
    int Scale = 2;

public:

    bool OnUserCreate() override
    {
        if (!csPGE2_logo.init(ScreenSize))
        {
            std::cout << "\nError while loading files for csPGE2_logo\n";
            return false;
        }

        #ifdef DEBUG_MODE

        DebugCreate();

        #endif

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (csPGE2_logo.Run(GetElapsedTime(), this)) return true;

        #ifdef DEBUG_MODE

        DebugUpdate(GetElapsedTime());

        #endif

        Clear(olc::BLACK);

        #ifdef DEBUG_MODE

        DebugDraw(this);

        #endif

        return true;
    }

    bool OnUserDestroy() override
    {
        #ifdef DEBUG_MODE

        DebugDestroy();

        #endif

        return true;
    }
};

#endif