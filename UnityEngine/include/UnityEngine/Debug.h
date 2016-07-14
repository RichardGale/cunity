#ifndef SRC_UNITYENGINE_DEBUG_H_
#define SRC_UNITYENGINE_DEBUG_H_

#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

namespace UnityEngine
{
    class Object;
    typedef Object* ObjectHandle;

    class String;
    
    class Exception
    {
    };

    struct LogType
    {
        enum Enum
        {
            Error,
            Assert,
            Warning,
            Log,
            Exception
        };
    };

    class ILogHandler
    {
    public:
        virtual void LogException(Exception exception, ObjectHandle context = nullptr) = 0;
        virtual void LogFormat(LogType::Enum logType, ObjectHandle context, String format, ...) = 0;
    };

    class ILogger : public ILogHandler
    {
    public:
        virtual LogType::Enum filterLogType() = 0;
        virtual void filterLogType(LogType::Enum value) = 0;
        virtual bool logEnabled() = 0;
        virtual void logEnabled(bool value) = 0;
        virtual ILogHandler* logHandler() = 0;
        virtual void logHandler(ILogHandler *value) = 0;
        virtual bool IsLogTypeAllowed(LogType::Enum logType) = 0;
        virtual void Log(LogType::Enum logType,
                         String message,
                         ObjectHandle context = nullptr) = 0;
        virtual void Log(LogType::Enum logType,
                         String tag,
                         String message,
                         ObjectHandle context = nullptr) = 0;
        virtual void Log(String message) = 0;
        virtual void Log(String tag, String message,
                         ObjectHandle context = nullptr) = 0;
        virtual void LogError(String tag, String message,
                              ObjectHandle context = nullptr) = 0;
        virtual void LogException(Exception exception,
                                  ObjectHandle context = nullptr) = 0;
        virtual void LogFormat(LogType::Enum logType,
                               ObjectHandle context,
                               String format, ...) = 0;
        virtual void LogWarning(String tag, String message,
                                ObjectHandle context = nullptr) = 0;
    };

    class Debug
    {
    public:
        static bool developerConsoleVisible();
        static void developerConsoleVisible(bool value);
        static bool isDebugBuild();
        static ILogger* logger();
        static void logger(ILogger *value);

        static void Assert(bool condition,
                           ObjectHandle context = nullptr);
        static void Assert(bool condition,
                           String message, ObjectHandle context = nullptr);
        static void AssertFormat(bool condition,
                                 String format, ...);
        static void AssertFormat(bool condition,
                                 ObjectHandle context,
                                 String format, ...);
        static void Break();
        static void ClearDeveloperConsole();
        static void DrawLine(Vector2 start,
                             Vector2 end,
                             Color color = Color::white,
                             float duration = 0.0f,
                             bool depthTest = true);
        static void DrawLine(Vector3 start,
                             Vector3 end,
                             Color color = Color::white,
                             float duration = 0.0f,
                             bool depthTest = true);
        static void DrawRay(Vector3 start,
                            Vector3 dir,
                            Color color = Color::white,
                            float duration = 0.0f,
                            bool depthTest = true);
        static void Log(String message,
                        ObjectHandle context = nullptr);
        static void LogAssertion(String message,
                                 ObjectHandle context = nullptr);
        static void LogAssertionFormat(String format, ...);
        static void LogAssertionFormat(ObjectHandle context,
                                       String format, ...);
        static void LogError(String message,
                             ObjectHandle context);
        static void LogErrorFormat(String format, ...);
        static void LogErrorFormat(ObjectHandle context,
                                   String format, ...);
        static void LogException(Exception exception,
                                 ObjectHandle context = nullptr);
        static void LogFormat(String format, ...);
        static void LogFormat(ObjectHandle context,
                              String format, ...);
        static void LogWarning(String message,
                               ObjectHandle context = nullptr);
        static void LogWarningFormat(String format, ...);
        static void LogWarningFormat(ObjectHandle context,
                                     String format, ...);

    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_DEBUG_H_
