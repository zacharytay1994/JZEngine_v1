/*	__FILE HEADER__
*	File:	Console.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Engine console system. Able to write to console
			through a static function Console::Log(const char*).
*/

#include "PCH.h"

#include "../ImGui/imgui.h"

#include "Console.h"
#include "../EngineConfig.h"
#include "../DebugTools/Log.h"

namespace JZEngine
{
    std::string* Console::currently_selected_console_{ nullptr };
    std::unordered_map<std::string, unsigned char>* Console::console_log_names_{ nullptr };
    bool Console::more_info_{ false };

    struct ConsoleLog
    {
        ImGuiTextBuffer     Buf;
        ImGuiTextFilter     Filter;
        bool                AutoScroll;    // Keep scrolling if already at the bottom.

        ConsoleLog()
        {
            AutoScroll = true;
            ResetLineOffsets();
        }

        void ResetLineOffsets(const std::string& name = "")
        {
            if (!name.empty())
            {
                Log::OSLogger& logger = Log::Instance().GetOSLogger(name);
                logger.lineoffset_.clear();
                logger.lineoffset_.push_back(0);
                logger.stripped_lineoffset_.clear();
                logger.stripped_lineoffset_.push_back(0);
            }
        }

        void Clear(const std::string& name)
        {
            Log::Instance().GetOSLogger(name).oss_.str("");
            Log::Instance().GetOSLogger(name).stripped_oss_.str("");
            ResetLineOffsets(name);
        }

        void Draw(const char* title, const std::string& name, bool* p_open = NULL)
        {
            if (!ImGui::Begin(title, p_open))
            {
                ImGui::End();
                return;
            }

            // Options menu
            if (ImGui::BeginPopup("Consoles"))
            {
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
                Clear(name);
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

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
            std::vector<unsigned int>& LineOffsets = Console::more_info_ ? 
                Log::Instance().GetOSLogger(name).lineoffset_ : Log::Instance().GetOSLogger(name).stripped_lineoffset_;
            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have a random access on the result on our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.size(); line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.size()) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        ImGui::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                for (int line_no = 0; line_no < LineOffsets.size(); line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.size()) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::EndChild();
            ImGui::End();
        }

        void RenderConsoleLog(bool* p_open, float x, float y, float sx, float sy)
        {
            ImGui::SetNextWindowBgAlpha(0.8f);
            ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x, static_cast<float>(Settings::window_height) * y }, ImGuiCond_Once);
            ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx, static_cast<float>(Settings::window_height) * sy }, ImGuiCond_Once);

            // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
            Draw("Console", *Console::currently_selected_console_, p_open);
        }
    };

	Console::Console(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{
        currently_selected_console_ = new std::string;
        console_log_names_ = new std::unordered_map<std::string, unsigned char>();
        console_log_ = new ConsoleLog();
        SetConsole("Main");
	}

    Console::~Console()
    {
        delete currently_selected_console_;
        delete console_log_names_;
        delete console_log_;
    }

	/*!
	 * @brief ___JZEngine::Console::Render()___
	 * ****************************************************************************************************
	 * Renders the console.
	 * ****************************************************************************************************
	*/
	void Console::Render()
	{
        bool open = true;
        console_log_->RenderConsoleLog(&open, x_, y_, sx_, sy_);
	}


    void Console::ExistConsoleLog(const std::string& name)
    {
        (*console_log_names_)[name];
    }

    void Console::SetConsole(const std::string& name)
    {
        *currently_selected_console_ = name;
    }
}