#ifndef PGE_CUT_SCENE
#define PGE_CUT_SCENE

#include "CutScenes.hpp"

class PGE_INTRO : public CutScene
{
private:
    olc::Decal *m_LOGO = nullptr;
    olc::Sprite *m_LOGOspr = nullptr;
    olc::vi2d m_LOGO_bounds;
    float m_LOGO_Opacity = 255;
    std::string m_PathToSprite = "pge2_logo.png";

public:
    PGE_INTRO()
    {
        files_to_load = {
            m_PathToSprite
        };

        Duration = 3.0f;
        m_TimerOffset = 3.0f;

    }
    ~PGE_INTRO(){}

    void LoadFiles() override
    {
        olc::Sprite *m_LOGOspr = new olc::Sprite(m_PathToSprite);
        m_LOGO = new olc::Decal(m_LOGOspr);
        m_LOGO_bounds = {m_LOGOspr->width, m_LOGOspr->height};
    }

    void update(float fElapsedTime) override
    {
        m_LOGO_Opacity = float(m_Timer + m_TimerOffset / Duration) * 255.0f;
        if (m_LOGO_Opacity < 0) m_LOGO_Opacity = 0;
        if (m_LOGO_Opacity > 255.0f) m_LOGO_Opacity = 255.0f;
    }

    void draw(olc::PixelGameEngine *pge) override
    {
        pge->Clear(olc::WHITE);
        pge->DrawDecal((m_WindowSize - m_LOGO_bounds) * 0.5f, m_LOGO, {1.0f,1.0f}, olc::Pixel(255,255,255,m_LOGO_Opacity));
    }
};

#endif