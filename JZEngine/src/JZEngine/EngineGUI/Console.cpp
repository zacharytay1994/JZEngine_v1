/*	__FILE HEADER__
*	File:	Console.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Engine console system. Able to write to console
			through a static function Console::Log(const char*).
*/

#include "PCH.h"
#include "Console.h"

#include "../ImGui/imgui.h"

#include "../EngineConfig.h"
#include "../DebugTools/Log.h"

namespace JZEngine
{
    std::string* Console::currently_selected_console_{ nullptr };
    std::unordered_map<std::string, unsigned char>* Console::console_log_names_{ nullptr };
    bool Console::more_info_{ true };
    //std::unordered_map<std::string, ConsoleLog>* Console::console_logs_{ nullptr };

    struct ConsoleLog
    {
        ImGuiTextBuffer     Buf;
        ImGuiTextFilter     Filter;
        ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
        bool                AutoScroll;  // Keep scrolling if already at the bottom.

        ConsoleLog()
        {
            AutoScroll = true;
            Clear();
        }

        void    Clear()
        {
            Buf.clear();
            LineOffsets.clear();
            LineOffsets.push_back(0);
        }

        void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
        {
            int old_size = Buf.size();
            va_list args;
            va_start(args, fmt);
            Buf.appendfv(fmt, args);
            va_end(args);
            for (int new_size = Buf.size(); old_size < new_size; old_size++)
                if (Buf[old_size] == '\n')
                    LineOffsets.push_back(old_size + 1);
        }

        void    Draw(const char* title, const std::string& name, bool* p_open = NULL)
        {
            if (!ImGui::Begin(title, p_open))
            {
                ImGui::End();
                return;
            }

            // Options menu
            if (ImGui::BeginPopup("Consoles"))
            {
                //ImGui::Checkbox("Auto-scroll", &AutoScroll);

                if (Console::console_log_names_)
                {
                    for (auto& cl : *Console::console_log_names_)
                    {
                        if (ImGui::Selectable(cl.first.c_str()))
                        {
                            Console::SetConsole(cl.first);
                        }
                    }
                }

                ImGui::EndPopup();
            }

            // Main window
            if (ImGui::Button((*Console::currently_selected_console_).c_str()))
                ImGui::OpenPopup("Consoles");
            ImGui::SameLine();
            if (Console::more_info_)
            {
                if (ImGui::Button("More"))
                {
                    Console::more_info_ = !Console::more_info_;
                }
            }
            else
            {
                if (ImGui::Button("Less"))
                {
                    Console::more_info_ = !Console::more_info_;
                }
            }
            ImGui::SameLine();
            bool clear = ImGui::Button("Clear");
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");
            ImGui::SameLine();
            Filter.Draw("Filter", -100.0f);

            ImGui::Separator();

            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            if (clear)
                Clear();
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            /*const char* buf = Buf.begin();
            const char* buf_end = Buf.end();*/

            std::string str;
            if (Console::more_info_)
            {
                str = Log::Instance().GetOSLogger(name).oss_.str();
            }
            else
            {
                str = Log::Instance().GetOSLogger(name).stripped_oss_.str();
            }
            const char* buf = str.begin()._Ptr;
            const char* buf_end = str.end()._Ptr;

            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have a random access on the result on our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        ImGui::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   ImGui::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using ImGuiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::EndChild();
            ImGui::End();
        }

        void RenderConsoleLog(bool* p_open, float x, float y, float sx, float sy)
        {
            // For the demo: add a debug button _BEFORE_ the normal log window contents
            // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
            // Most of the contents of the window will be added by the log.Draw() call.
            ImGui::SetNextWindowBgAlpha(0.8f);
            ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x, static_cast<float>(Settings::window_height) * y }, ImGuiCond_Once);
            ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx, static_cast<float>(Settings::window_height) * sy }, ImGuiCond_Once);
            /*ImGui::Begin("Example: Log", p_open);
            if (ImGui::SmallButton("[Debug] Add 5 entries"))
            {
                static int counter = 0;
                const char* categories[3] = { "info", "warn", "error" };
                const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
                for (int n = 0; n < 5; n++)
                {
                    const char* category = categories[counter % IM_ARRAYSIZE(categories)];
                    const char* word = words[counter % IM_ARRAYSIZE(words)];
                    AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                        ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
                    counter++;
                }
            }

            ImGui::End();*/
            // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
            Draw("Console", *Console::currently_selected_console_, p_open);
        }
    };
    //ConsoleLog* Console::console_log_;

    //ConsoleLog console_log("log1");

	//unsigned int Console::console_line_number_{ 0 };
	//std::stringstream Console::console_stream_;

	Console::Console(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{
        currently_selected_console_ = new std::string;
        console_log_names_ = new std::unordered_map<std::string, unsigned char>();
        console_log_ = new ConsoleLog();
        //console_logs_ = new std::unordered_map<std::string, ConsoleLog>();

        //CreateConsoleLog("Main");
        //Log::Instance().GetOSLogger("Main").logger_->set_pattern("%@, %v");
        SetConsole("Main");
        //Log::Instance().OSLog("Main")->info("Main Console Ready.");
        //Log::Instance().OSLog("Main")->critical("something");
        //Log::Instance().OSLog("Main")->info("something {}");
        //Log::Instance().Info("Main", "someting {} strange {}", 0.124f, "in the neighbourhood");
        ////*currently_selected_console_ = "Main";
        ////CreateConsoleLog("Test");
        ////CreateConsoleLog("Math");

        //Log::Instance().OSLog("Main")->info("testing console log");
        //for (int i = 0; i < 200; ++i)
        //{
        //    Log::Instance().OSLog("Main")->info("test os logger {}", i);
        //}
        //Log::Instance().OSLog("Test")->info("test test console");
        Log::Info("StaticInfo", "this is static info {}", "number 1");
        Log::Info("Test", "testing {}", 1.234f);
        Log::Info("Main", "testing {}", 1.234f);
        Log::Warning("Math", "warning {}", 1.234f);
        Log::Warning("Main", "warning {}", 1.234f);
        Log::Error("Main", "error {}", 1.234f);
        Log::Critical("Main", "warnicriticalng {}", 1.234f);
        Log::Critical("Math", "warnicriticalng {}", 1.234f);
        for (int i = 0; i < 20; ++i)
        {
            Log::Info("StaticInfo", "this is static info {}", i);
        }
	}

    Console::~Console()
    {
        delete currently_selected_console_;
        delete console_log_names_;
        delete console_log_;
        //delete console_logs_;
    }

	/*!
	 * @brief ___JZEngine::Console::Render()___
	 * ****************************************************************************************************
	 * Renders the console.
	 * ****************************************************************************************************
	*/
	void Console::Render()
	{
		/*ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Once);*/
		//ImGui::Begin("Console");
		////ImGui::Text(console_stream_.str().c_str());
		//ImGui::End();
        bool open = true;
        //console_log.RenderConsoleLog(&open, x_, y_, sx_, sy_);
        console_log_->RenderConsoleLog(&open, x_, y_, sx_, sy_);
	}


    void Console::ExistConsoleLog(const std::string& name)
    {
        (*console_log_names_)[name];
        //(*console_logs_)[name] = ConsoleLog(name);
        //Log::Instance().GetOSLogger(name);
    }

    void Console::SetConsole(const std::string& name)
    {
        *currently_selected_console_ = name;
        /*if (more_info_)
        {
            Log::Instance().GetOSLogger(name).logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");
        }
        else
        {
            Log::Instance().GetOSLogger(name).logger_->set_pattern("%v");
        }*/
    }
}