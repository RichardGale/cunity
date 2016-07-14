#ifndef SRC_UNITYENGINE_TIME_H_
#define SRC_UNITYENGINE_TIME_H_

namespace UnityEngine
{
    class Time
    {
    public:
        static int captureFramerate();
        static void captureFramerate(int value);
        static float deltaTime();
        static float fixedDeltaTime();
        static void fixedDeltaTime(float value);
        static float fixedTime();
        static int frameCount();
        static float maximumDeltaTime();
        static void maximumDeltaTime(float value);
        static float realtimeSinceStartup();
        static float smoothDeltaTime();
        static float time();
        static float timeScale();
        static void timeScale(float scale);
        static float timeSinceLevelLoad();
        static float unscaledDeltaTime();
        static float unscaledTime();
    private:
        static int m_captureFramerate;
        static float m_fixedDeltaTime;
        static float m_maximumDeltaTime;
        static float m_timeScale;

        static float m_realtimeSinceStartup; // += dt
        static float m_timeSinceLevelLoad; // += dt
        static float m_deltaTime; // = dt
        static float m_time; // += dt
        static int m_frameCount; // ++
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_TIME_H_
