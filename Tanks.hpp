#ifndef TANKS_ENGINE_HPP
#define TANKS_ENGINE_HPP

#include "olcPixelGameEngine.hpp"
#include "FileChecker.hpp"
#include "PGE_intro.hpp"
#include "Player.hpp"

#include <string>

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
    int LayerBG = 0;
    int LayerMG = 0;
    int LayerUI = 0;

private:
    PGE_INTRO csPGE2_logo;

    Player csPlayer;

    Sprite *sprCrosshair = nullptr;
    Decal *decCrosshair = nullptr;
    std::string pathToCrosshair = "crosshair.png";
    vf2d CrosshairSize;

    Sprite *sprFloorTile = nullptr;
    Sprite *sprFloorBG = nullptr;
    Decal *decFloorBG = nullptr;
    std::string pathToFloorTile = "FloorBG.png";
    vf2d FloorBoardSize;

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

        // 0-------------------------------------------------------0
        // 0 Load Files for the game and initialize Sprites/Decals 0
        // 0-------------------------------------------------------0
        if (!csPGE2_logo.init(ScreenSize))
        {
            std::cout << "Error while loading files for csPGE2_logo!\n";
            return false;
        }

        if (!csPlayer.init())
        {
            std::cout << "Error while loading files for csPlayer!\n";
            return false;
        }

        if (!file::doesExist(pathToCrosshair))
        {
            std::cout << "Error while loading image for Crosshair!\n";
            return false;
        }
        else
        {
            sprCrosshair = new Sprite(pathToCrosshair);
            decCrosshair = new Decal(sprCrosshair);
            CrosshairSize = {(float)sprCrosshair->width, (float)sprCrosshair->height};
        }

        if (!file::doesExist(pathToFloorTile))
        {
            std::cout << "Error while loading image for FloorBoards!\n";
            return false;
        }
        else
        {
            sprFloorBG = new Sprite(pathToFloorTile);
            decFloorBG = new Decal(sprFloorBG);
            FloorBoardSize = {(float)sprFloorBG->width,(float)sprFloorBG->height};
        }

        // 0----------------------------0
        // 0 End Loading Files for Game 0
        // 0----------------------------0

        // 0----------------------------0
        // 0  Setup Layers for Drawing  0
        // 0----------------------------0

        //Initialize the MainGame Layer
        LayerMG = CreateLayer();
        EnableLayer(LayerMG, true);
        SetDrawTarget(LayerMG);
        SetPixelMode(Pixel::ALPHA);
        Clear(BLANK);

        //Initialize the background Layer
        LayerBG = CreateLayer();
        EnableLayer(LayerBG, true);
        SetDrawTarget(LayerBG);
        SetPixelMode(Pixel::ALPHA);
        Clear(BLANK);

        SetDrawTarget((int)0);

        // 0----------------------------0
        // 0      End Layer Setup       0
        // 0----------------------------0



        #ifdef DEBUG_MODE

        DebugCreate();

        #endif

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        #ifndef DEBUG_MODE
        if (csPGE2_logo.Run(GetElapsedTime(), this)) return true;
        #endif

        #ifdef DEBUG_MODE

        DebugUpdate(GetElapsedTime());

        #endif

        Clear(BLANK);

        SetDrawTarget(LayerBG);
        Clear(olc::BLACK);
        DrawDecal({0,0}, decFloorBG);

        SetDrawTarget(LayerMG);
        Clear(BLANK);

        if (csPlayer.Run(GetMousePos(), GetElapsedTime(), this))
        {
            
        }
        else
        {
            csPlayer.spawn(ScreenSize/2);
        }

        DrawDecal(GetMousePos() - CrosshairSize/2, decCrosshair,{1,1},csPlayer.getColor());

        float distanceCursorAndPlayer = (csPlayer.getPos() - GetMousePos()).mag();
        int numberOfCircles = 6;

        if (distanceCursorAndPlayer >= 128)
        for (int i = 0; i < numberOfCircles - 1; i++) //Draw a dotted line between player and crosshair
        {
            DrawCircle(GetMousePos() + (csPlayer.getPos() - GetMousePos()).norm() * distanceCursorAndPlayer / numberOfCircles * (i + 1), 3,Pixel(24,20,27));
            FillCircle(GetMousePos() + (csPlayer.getPos() - GetMousePos()).norm() * distanceCursorAndPlayer / numberOfCircles * (i + 1), 2, csPlayer.getColor());
        }
        

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