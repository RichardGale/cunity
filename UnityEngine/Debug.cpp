#include "UnityEngine/Debug.h"

#include <stdarg.h>

#include "UnityEngine/Unity.h"

#include "imgui/imgui.h"

#define IM_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))

// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    bool                  ScrollToBottom;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImVector<const char*> Commands;

    ExampleAppConsole()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");  // "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
        AddLog("Welcome to ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            free(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* str1, const char* str2)         { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
    static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
    static char* Strdup(const char* str)                             { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }

    void ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
        {
            free(Items[i]);
        }
        Items.clear();
        ScrollToBottom = true;
    }

    void AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
    {
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
        ScrollToBottom = true;
    }

    void Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520,600), ImGuiSetCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        if (ImGui::SmallButton("Clear"))
        {
            ClearLog();
            ImGui::SameLine();
        }
        if (ImGui::SmallButton("Scroll to bottom"))
        {
            ScrollToBottom = true;
        }

        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
        static ImGuiTextFilter filter;
        filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::PopStyleVar();
        ImGui::Separator();

        ImGui::BeginChild("ScrollingRegion", ImVec2(0,-ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear"))
            {
                ClearLog();
            }
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
        // You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
        // To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
        //     ImGuiListClipper clipper(Items.Size);
        //     while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // However take note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
        // If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!filter.PassFilter(item))
                continue;
            ImVec4 col = ImVec4(1.0f,1.0f,1.0f,1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
            if (strstr(item, "[error]"))
            {
                col = ImColor(1.0f,0.4f,0.4f,1.0f);
            }
            else if (strncmp(item, "# ", 2) == 0)
            {
                col = ImColor(1.0f,0.78f,0.58f,1.0f);
            }
            ImGui::PushStyleColor(ImGuiCol_Text, col);
            ImGui::TextUnformatted(item);
            ImGui::PopStyleColor();
        }
        if (ScrollToBottom)
        {
            ImGui::SetScrollHere();
        }
        ScrollToBottom = false;
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
        {
            char* input_end = InputBuf+strlen(InputBuf);
            while (input_end > InputBuf && input_end[-1] == ' ') input_end--; *input_end = 0;
            if (InputBuf[0])
            {
                ExecCommand(InputBuf);
            }
            strcpy(InputBuf, "");
        }

        // Demonstrate keeping auto focus on the input box
        if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
        {
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
        }

        ImGui::End();
    }

    void ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size-1; i >= 0; i--)
        {
            if (Stricmp(History[i], command_line) == 0)
            {
                free(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            for (int i = History.Size >= 10 ? History.Size - 10 : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }
    }

    static int TextEditCallbackStub(ImGuiTextEditCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int TextEditCallback(ImGuiTextEditCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
            case ImGuiInputTextFlags_CallbackCompletion:
            {
                // Example of TEXT COMPLETION

                // Locate beginning of current word
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    const char c = word_start[-1];
                    if (c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }

                // Build a list of candidates
                ImVector<const char*> candidates;
                for (int i = 0; i < Commands.Size; i++)
                    if (Strnicmp(Commands[i], word_start, (int)(word_end-word_start)) == 0)
                        candidates.push_back(Commands[i]);

                if (candidates.Size == 0)
                {
                    // No match
                    AddLog("No match for \"%.*s\"!\n", (int)(word_end-word_start), word_start);
                }
                else if (candidates.Size == 1)
                {
                    // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                    data->DeleteChars((int)(word_start-data->Buf), (int)(word_end-word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                    int match_len = (int)(word_end - word_start);
                    for (;;)
                    {
                        int c = 0;
                        bool all_candidates_matches = true;
                        for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }

                    if (match_len > 0)
                    {
                        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end-word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }

                    // List matches
                    AddLog("Possible matches:\n");
                    for (int i = 0; i < candidates.Size; i++)
                        AddLog("- %s\n", candidates[i]);
                }

                break;
            }
            case ImGuiInputTextFlags_CallbackHistory:
            {
                // Example of HISTORY
                const int prev_history_pos = HistoryPos;
                if (data->EventKey == ImGuiKey_UpArrow)
                {
                    if (HistoryPos == -1)
                        HistoryPos = History.Size - 1;
                    else if (HistoryPos > 0)
                        HistoryPos--;
                }
                else if (data->EventKey == ImGuiKey_DownArrow)
                {
                    if (HistoryPos != -1)
                        if (++HistoryPos >= History.Size)
                            HistoryPos = -1;
                }

                // A better implementation would preserve the data on the current input line along with cursor position.
                if (prev_history_pos != HistoryPos)
                {
                    data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
                    data->BufDirty = true;
                }
            }
        }
        return 0;
    }
};

static ExampleAppConsole* console = nullptr;
static bool open = true;

void Debug_DrawDeveloperConsole()
{
    if (UnityEngine::Debug::developerConsoleVisible())
    {
        if (console == nullptr)
        {
            console = new ExampleAppConsole();
        }
        console->Draw("Developer Console", &open);
    }
}

namespace UnityEngine
{
    static String kTag = "cunity";

    class DefaultLogHandler : public ILogHandler
    {
    public:
        virtual void LogException(Exception exception, ObjectHandle context = nullptr)
        {
        }

        virtual void LogFormat(LogType::Enum logType, ObjectHandle context, String format, ...)
        {
            va_list args;
            va_start(args, format);
            vprintf(format.c_str(), args);
            printf("\n");
            if (console == nullptr)
            {
                console = new ExampleAppConsole();
            }
            console->AddLog(format.c_str(), args);
        }
    };

    class DefaultLogger : public ILogger
    {
    public:
        DefaultLogger()
        : m_filter(LogType::Log)
        , m_enabled(true)
        , m_logHandler(new DefaultLogHandler())
        {
        }

        virtual LogType::Enum filterLogType()
        {
            return m_filter;
        }

        virtual void filterLogType(LogType::Enum value)
        {
            m_filter = value;
        }

        virtual bool logEnabled()
        {
            return m_enabled;
        }

        virtual void logEnabled(bool value)
        {
            m_enabled = value;
        }

        virtual ILogHandler* logHandler()
        {
            return m_logHandler;
        }

        virtual void logHandler(ILogHandler *value)
        {
            m_logHandler = value;
        }

        virtual bool IsLogTypeAllowed(LogType::Enum logType)
        {
            return (logType <= m_filter);
        }

        virtual void Log(LogType::Enum logType, String message, ObjectHandle context)
        {
            Log(logType, kTag, message, context);
        }

        virtual void Log(LogType::Enum logType, String tag, String message, ObjectHandle context)
        {
            if (IsLogTypeAllowed(logType))
            {
                m_logHandler->LogFormat(logType, context, message);
            }
        }

        virtual void Log(String message)
        {
            Log(LogType::Log, kTag, message, nullptr);
        }

        virtual void Log(String tag, String message, ObjectHandle context)
        {
            Log(LogType::Log, kTag, message, context);
        }

        virtual void LogError(String tag, String message, ObjectHandle context)
        {
            Log(LogType::Error, tag, message, context);
        }

        virtual void LogException(Exception exception, ObjectHandle context)
        {
            if (IsLogTypeAllowed(LogType::Exception))
            {
                m_logHandler->LogException(exception, context);
            }
        }

        virtual void LogFormat(LogType::Enum logType, ObjectHandle context, String format, ...)
        {
            if (IsLogTypeAllowed(logType))
            {
                va_list args;
                va_start(args, format);

                char message[1023+1];
                vsnprintf(message, sizeof(message), format.c_str(), args);
                Log(logType, kTag, message, context);
            }
        }

        virtual void LogWarning(String tag, String message, ObjectHandle context)
        {
            Log(LogType::Warning, kTag, message, context);
        }

    private:
        LogType::Enum m_filter;
        bool m_enabled;
        ILogHandler *m_logHandler;
    };

    static bool s_consoleVisible = true;
    static ILogger* s_logger = new DefaultLogger();

    bool Debug::developerConsoleVisible()
    {
        return s_consoleVisible;
    }

    void Debug::developerConsoleVisible(bool value)
    {
        s_consoleVisible = value;
    }

    bool Debug::isDebugBuild()
    {
#if defined(NDEBUG)
        return false;
#else
        return true;
#endif
    }

    ILogger* Debug::logger()
    {
        return s_logger;
    }

    void Debug::logger(ILogger *value)
    {
        s_logger = value;
    }

    void Debug::Assert(bool condition, ObjectHandle context)
    {
        if (!condition)
        {
            s_logger->Log(LogType::Assert, "Assertion failed.", context);
        }
    }

    void Debug::Assert(bool condition, String message, ObjectHandle context)
    {
        if (!condition)
        {
            s_logger->Log(LogType::Assert, message, context);
        }
    }

    void Debug::AssertFormat(bool condition, String format, ...)
    {
        if (!condition)
        {
            s_logger->LogFormat(LogType::Assert, nullptr, format);
        }
    }

    void Debug::AssertFormat(bool condition, ObjectHandle context, String format, ...)
    {
        if (!condition)
        {
            s_logger->LogFormat(LogType::Assert, context, format);
        }
    }

    void Debug::Break()
    {
    }

    void Debug::ClearDeveloperConsole()
    {
    }

    void Debug::DrawLine(Vector2 start,
                         Vector2 end,
                         Color color,
                         float duration,
                         bool depthTest)
    {
    }

    void Debug::DrawLine(Vector3 start,
                         Vector3 end,
                         Color color,
                         float duration,
                         bool depthTest)
    {
    }

    void Debug::DrawRay(Vector3 start,
                        Vector3 dir,
                        Color color,
                        float duration,
                        bool depthTest)
    {
        dir += static_cast<glm::vec3>(start); // ugh
        DrawLine(start, dir, color, duration, depthTest);
    }

    void Debug::Log(String message, ObjectHandle context)
    {
        s_logger->LogFormat(LogType::Log, nullptr, message);
    }

    void Debug::LogAssertion(String message, ObjectHandle context)
    {
        s_logger->LogFormat(LogType::Assert, context, message);
    }

    void Debug::LogAssertionFormat(String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogFormat(LogType::Assert, nullptr, msg);
    }

    void Debug::LogAssertionFormat(ObjectHandle context, String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogFormat(LogType::Assert, context, msg);
    }

    void Debug::LogError(String message, ObjectHandle context)
    {
        s_logger->LogError(kTag, message, context);
    }

    void Debug::LogErrorFormat(String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogError(kTag, msg, nullptr);
    }

    void Debug::LogErrorFormat(ObjectHandle context, String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogError(kTag, msg, context);
    }

    void Debug::LogException(Exception exception, ObjectHandle context)
    {
        s_logger->LogException(exception, context);
    }

    void Debug::LogFormat(String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogFormat(LogType::Log, nullptr, msg);
    }

    void Debug::LogFormat(ObjectHandle context, String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogFormat(LogType::Log, context, msg);
    }

    void Debug::LogWarning(String message, ObjectHandle context)
    {
        s_logger->LogWarning(kTag, message, context);
    }

    void Debug::LogWarningFormat(String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogWarning(kTag, msg, nullptr);
    }

    void Debug::LogWarningFormat(ObjectHandle context, String format, ...)
    {
        char msg[1023+1];
        va_list args;
        va_start(args, format);
        vsnprintf(msg, sizeof(msg), format.c_str(), args);

        s_logger->LogWarning(kTag, msg, context);
    }
}  // namespace UnityEngine
