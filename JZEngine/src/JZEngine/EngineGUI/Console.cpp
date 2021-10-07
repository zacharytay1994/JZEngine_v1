/*	__FILE HEADER__
*	File:	    Console.cpp
	Primary:    Zachary Tay
	Date:	    26/08/21
	Brief:	    Engine console system. Able to write to console
			    through a static function Console::Log(const char*).
*/

#include "PCH.h"

#include "../ImGui/imgui.h"

#include "Console.h"
#include "../EngineConfig.h"
#include "../DebugTools/Log.h"
#include "MenuBar.h"

namespace JZEngine
{
    //std::string*                                    Console::currently_selected_console_{ nullptr };    /*!< the currently displayed console */
    //std::unordered_map<std::string, unsigned char>* Console::console_log_names_{ nullptr };             /*!< all consoles */
    //bool                                            Console::more_info_{ false };                       /*!< if log information is more/less */

    /*!
     * @brief ___JZEngine::ConsoleLog___
	 * ****************************************************************************************************
     * The ImGui console log.
	 * ****************************************************************************************************
    */
    struct ConsoleLog
    {
        Console&            console_;
        ImGuiTextFilter     Filter;
        bool                AutoScroll;    // Keep scrolling if already at the bottom.

        ConsoleLog(Console& console)
            :
            console_(console)
        {
            AutoScroll = true;
        }

        /*!
         * @brief ___JZEngine::ConsoleLog::ResetLineOffsets()___
		 * ****************************************************************************************************
         * @param name
         * : Reset console lineoffsets.
		 * ****************************************************************************************************
        */
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

        /*!
         * @brief ___JZEngine::ConsoleLog::Clear()___
		 * ****************************************************************************************************
         * Clears the console.
		 * ****************************************************************************************************
         * @param name 
         * : The console to clear.
		 * ****************************************************************************************************
        */
        void Clear(const std::string& name)
        {
            Log::Instance().GetOSLogger(name).oss_.str("");
            Log::Instance().GetOSLogger(name).stripped_oss_.str("");
            ResetLineOffsets(name);
        }

        /*!
         * @brief ___JZEngine::ConsoleLog::Draw()___
		 * ****************************************************************************************************
         * Renders the ImGui console.
		 * ****************************************************************************************************
         * @param title 
         * : ImGui console title.
         * @param name 
         * : Console to render.
		 * ****************************************************************************************************
        */
        void Draw(const char* title, const std::string& name, bool* p_open = NULL)
        {
            if (!ImGui::Begin(title, p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
            {
                ImGui::End();
                return;
            }

            // display selection for all the consoles
            if (ImGui::BeginPopup("Consoles"))
            {
                if (console_.console_log_names_)
                {
                    for (auto& cl : *console_.console_log_names_)
                    {
                        if (ImGui::Selectable(cl.first.c_str()))
                        {
                            console_.SetConsole(cl.first);
                        }
                    }
                }
                ImGui::EndPopup();
            }

            // button event to display all console options
            if (ImGui::Button((*console_.currently_selected_console_).c_str()))
                ImGui::OpenPopup("Consoles");
            ImGui::SameLine();

            // switch between 2 logging modes, more/less info
            if (console_.more_info_)
            {
                if (ImGui::Button("More"))
                {
                    console_.more_info_ = !console_.more_info_;
                }
            }
            else
            {
                if (ImGui::Button("Less"))
                {
                    console_.more_info_ = !console_.more_info_;
                }
            }
            ImGui::SameLine();

            // to clear the console
            bool clear = ImGui::Button("Clear");
            ImGui::SameLine();
            Filter.Draw("Filter", -100.0f);

            ImGui::Separator();

            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            if (clear)
                Clear(name);

            // draws the text part
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            std::string str;

            // get text data based on more/less info
            if (console_.more_info_)
            {
                str = Log::Instance().GetOSLogger(name).oss_.str();
            }
            else
            {
                str = Log::Instance().GetOSLogger(name).stripped_oss_.str();
            }
            const char* buf = str.begin()._Ptr;
            const char* buf_end = str.end()._Ptr;
            std::vector<unsigned int>& LineOffsets = console_.more_info_ ?
                Log::Instance().GetOSLogger(name).lineoffset_ : Log::Instance().GetOSLogger(name).stripped_lineoffset_;
            if (Filter.IsActive())
            {
                // renders the text for each line with filter
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
                // renders the text for each line no filter
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

        // renders the console log with ImGui widget attributes
        void RenderConsoleLog(bool* p_open, float x, float y, float sx, float sy)
        {
            ImGui::SetNextWindowBgAlpha(1.0f);
            ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x, MenuBar::height_ + static_cast<float>(Settings::window_height - MenuBar::height_) * y }, ImGuiCond_Always);
            ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx, static_cast<float>(Settings::window_height - MenuBar::height_) * sy }, ImGuiCond_Always);
            Draw("Console", *console_.currently_selected_console_, p_open);
        }
    };

	Console::Console(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{
        currently_selected_console_ = new std::string;
        console_log_names_ = new std::unordered_map<std::string, unsigned char>();
        console_log_ = new ConsoleLog(*this);
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

    /*!
     * @brief ___JZEngine::Console::ExistConsoleLog()___
     * ****************************************************************************************************
     * Checks if the console log already exist in the
     * map, else creates it.
     * ****************************************************************************************************
     * @param name
     * : The name of the console log.
     * ****************************************************************************************************
    */
    void Console::ExistConsoleLog(const std::string& name)
    {
        (*console_log_names_)[name];
    }

    /*!
     * @brief ___JZEngine::Console::SetConsole()___
     * ****************************************************************************************************
     * Sets the currently displayed console.
     * ****************************************************************************************************
     * @param name
     * : The console to display.
     * ****************************************************************************************************
    */
    void Console::SetConsole(const std::string& name)
    {
        *currently_selected_console_ = name;
    }
}