#ifndef CUT_SCENES_HPP
#define CUT_SCENES_HPP

#include "olcPixelGameEngine.hpp"
#include "FileChecker.hpp"

enum class CutSceneState { PLAYING=1, FINISHED=0 };

class CutScene : public olc::PGEX
{
protected:
    CutSceneState m_CS_State = CutSceneState::PLAYING;
    olc::vf2d m_WindowSize;
    float m_Timer;
    float m_TimerOffset = 0.0f;

public:
    CutScene(){}
    ~CutScene(){}

    std::vector<std::string> files_to_load;

    float Duration = 2.0f;

    bool init(olc::vf2d vecScreenSize)
    {
        m_Timer = Duration;

        m_WindowSize = vecScreenSize;

        bool success = file::batchDoesExist(files_to_load);

        if (success)
        LoadFiles();
        
        return success;
    }

    virtual void LoadFiles()
    {

    }

    bool Run(float fElapsedTime, olc::PixelGameEngine *pge)
    {
        if (m_CS_State == CutSceneState::FINISHED) return false;

        if (m_CS_State == CutSceneState::PLAYING)
        {
            m_Timer -= fElapsedTime;
            if (m_Timer <= 0.0f - m_TimerOffset)
            m_CS_State = CutSceneState::FINISHED;

            update(fElapsedTime);
            draw(pge);

            return true;
        }

        return false;;
    }
    
    virtual void update(float fElapsedTime)
    {

    }

    virtual void draw(olc::PixelGameEngine *pge)
    {

    }
};

#endif