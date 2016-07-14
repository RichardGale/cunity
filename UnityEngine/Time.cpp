#include "UnityEngine/Time.h"

namespace UnityEngine
{
    int Time::m_captureFramerate = 0;
    float Time::m_fixedDeltaTime = 0.0f;
    float Time::m_maximumDeltaTime = 0.0f;
    float Time::m_timeScale = 0.0f;
    float Time::m_realtimeSinceStartup = 0.0f;  // += dt
    float Time::m_timeSinceLevelLoad = 0.0f;  // += dt
    float Time::m_deltaTime = 0.0f;  // = dt
    float Time::m_time = 0.0f;  // += dt
    int Time::m_frameCount = 0;  // ++

    int Time::captureFramerate()
    {
        return m_captureFramerate;
    }

    void Time::captureFramerate(int value)
    {
        m_captureFramerate = value;
    }

    float Time::deltaTime()
    {
        return m_deltaTime*m_timeScale;
    }

    float Time::fixedDeltaTime()
    {
        return m_fixedDeltaTime;
    }

    void Time::fixedDeltaTime(float value)
    {
        m_fixedDeltaTime = value;
    }

    float Time::fixedTime()
    {
        return 0.0f;
    }

    int Time::frameCount()
    {
        return m_frameCount;
    }

    float Time::maximumDeltaTime()
    {
        return m_maximumDeltaTime;
    }

    void Time::maximumDeltaTime(float value)
    {
        m_maximumDeltaTime = value;
    }

    float Time::realtimeSinceStartup()
    {
        return m_realtimeSinceStartup;
    }

    float Time::smoothDeltaTime()
    {
        // http://forum.unity3d.com/threads/time-smoothdeltatime.10253/
        return 0.0f;
    }

    float Time::time()
    {
        return m_time*m_timeScale;
    }

    float Time::timeScale()
    {
        return m_timeScale;
    }

    void Time::timeScale(float scale)
    {
        m_timeScale = scale;
    }

    float Time::timeSinceLevelLoad()
    {
        return m_timeSinceLevelLoad;
    }

    float Time::unscaledDeltaTime()
    {
        return m_deltaTime;
    }

    float Time::unscaledTime()
    {
        return m_time;
    }
}  // namespace UnityEngine
