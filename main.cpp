//This software is licensed under the OLC-3 licence.

#define OLC_PGE_APPLICATION
#define DEBUG_MODE
#include "Tanks.hpp"

int main(int argc, char const *argv[])
{
    Tanks demo;
    if (demo.Construct(demo.ScreenSize.x, demo.ScreenSize.y, demo.Scale, demo.Scale))
    {
        demo.Start();
        return 0;
    }
    else
    {
        std::cout << "Couldn't construct Tanks in main.cpp";
        return 1;
    }
}
