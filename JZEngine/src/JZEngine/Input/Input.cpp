/*	__FILE HEADER__
*	File:		Input.cpp
    Primary:	Deon Khong
    Date:		26/08/21
    Brief:		Wraps GLFW input.
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "PCH.h"
#include "Input.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "../EngineConfig.h"
#include "../GraphicRendering/Camera.h"
namespace JZEngine
{
    // static data members declared in InputHandler
    std::unordered_map<int, bool> InputHandler::keystate;
    std::unordered_map<int, bool> InputHandler::prevkeystate;
    std::unordered_map<int, bool> InputHandler::mousestate;
    std::unordered_map<int, bool> InputHandler::prevmousestate;
    Vec2f InputHandler::mousepos;
    int InputHandler::mouse_scrolled_{ 0 };
    

    bool InputHandler::init(GLFWwindow* ptr) {
        if (ptr==nullptr)
            return false;

        glfwSetKeyCallback(ptr, InputHandler::key_cb);
        glfwSetMouseButtonCallback(ptr, InputHandler::mousebutton_cb);
        glfwSetCursorPosCallback(ptr, InputHandler::mousepos_cb);
        glfwSetScrollCallback(ptr, InputHandler::mousescroll_cb);
        glfwSetInputMode(ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        return true;
    }

    void InputHandler::FrameEnd()
    {
        for (auto& it : mousestate) {
            prevmousestate[it.first] = it.second;
        }
        for (auto& it : keystate) {
            prevkeystate[it.first] = it.second;
        }
        mouse_scrolled_ = 0;
    }

    /*  _________________________________________________________________________*/
    /*! key_cb

    @param GLFWwindow*
    Handle to window that is receiving event

    @param int
    the keyboard key that was pressed or released

    @parm int
    Platform-specific scancode of the key

    @parm int
    GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
    action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
    for example E-mail and Play keys.

    @parm int
    bit-field describing which modifier keys (shift, alt, control)
    were held down

    @return none

    This function is called when keyboard buttons are pressed.
    When the ESC key is pressed, the close flag of the window is set.
    */
    void InputHandler::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod) {
        UNREFERENCED_PARAMETER(pwin);
        UNREFERENCED_PARAMETER(scancode);
        UNREFERENCED_PARAMETER(mod);
        if (GLFW_PRESS == action || GLFW_REPEAT == action)
            keystate[key] = true;
        else if (GLFW_RELEASE == action)
            keystate[key] = false;
    }

    /*  _________________________________________________________________________*/
    /*! mousebutton_cb

    @param GLFWwindow*
    Handle to window that is receiving event

    @param int
    the mouse button that was pressed or released
    GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
    mouse buttons are most useful

    @parm int
    action is either GLFW_PRESS or GLFW_RELEASE

    @parm int
    bit-field describing which modifier keys (shift, alt, control)
    were held down

    @return none

    This function is called when mouse buttons are pressed.
    */
    void InputHandler::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {
        UNREFERENCED_PARAMETER(mod);
        UNREFERENCED_PARAMETER(pwin);
        if(GLFW_PRESS == action || GLFW_REPEAT == action)
            mousestate[button] = true;
        else if (GLFW_RELEASE == action)
            mousestate[button] = false;
    }

    /*  _________________________________________________________________________*/
    /*! mousepos_cb

    @param GLFWwindow*
    Handle to window that is receiving event

    @param double
    new cursor x-coordinate, relative to the left edge of the client area

    @param double
    new cursor y-coordinate, relative to the top edge of the client area

    @return none

    This functions receives the cursor position, measured in screen coordinates but
    relative to the top-left corner of the window client area.
    */
    void InputHandler::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
        UNREFERENCED_PARAMETER(pwin);
        mousepos = { static_cast<float>(xpos),static_cast<float>(ypos) };
    }

    /*  _________________________________________________________________________*/
    /*! mousescroll_cb

    @param GLFWwindow*
    Handle to window that is receiving event

    @param double
    Scroll offset along X-axis

    @param double
    Scroll offset along Y-axis

    @return none

    This function is called when the user scrolls, whether with a mouse wheel or
    touchpad gesture. Although the function receives 2D scroll offsets, a simple
    mouse scroll wheel, being vertical, provides offsets only along the Y-axis.
    */
    void InputHandler::mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset) {

        UNREFERENCED_PARAMETER(pwin);
        UNREFERENCED_PARAMETER(xoffset);
        mouse_scrolled_ = static_cast<int>(yoffset);
    }

    /*  _________________________________________________________________________ */
    /*! error_cb

    @param int
    GLFW error code

    @parm char const*
    Human-readable description of the code

    @return none

    The error callback receives a human-readable description of the error and
    (when possible) its cause.
    */
    void InputHandler::error_cb(int error, char const* description) {
#ifdef _DEBUG
        UNREFERENCED_PARAMETER(error);
        std::cerr << "GLFW error: " << description << std::endl;
#endif
    }

    /*  _________________________________________________________________________ */
    /*! fbsize_cb

    @param GLFWwindow*
    Handle to window that is being resized

    @parm int
    Width in pixels of new window size

    @parm int
    Height in pixels of new window size

    @return none

    This function is called when the window is resized - it receives the new size
    of the window in pixels.
    */
    void InputHandler::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
#ifdef _DEBUG
        std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
        UNREFERENCED_PARAMETER(ptr_win);
        UNREFERENCED_PARAMETER(width);
        UNREFERENCED_PARAMETER(height);
    }

    bool InputHandler::IsKeyPressed(KEY key) 
    {
        if (keystate[static_cast<int>(key)] == true)
            return true;

        else return false;
    }
    bool InputHandler::IsKeyTriggered(KEY key)
    {
        if (keystate[static_cast<int>(key)] == true && prevkeystate[static_cast<int>(key)] == false)
        {
            
            return true;
        }

        else return false;
    }

    bool InputHandler::IsKeyReleased(KEY key)
    {
        if (keystate[static_cast<int>(key)] == false && prevkeystate[static_cast<int>(key)] == true)
        {

            return true;
        }

        else return false;
    }

    Vec2f InputHandler::GetMousePosition()
    {
        return mousepos;
    }

    bool InputHandler::IsMousePressed(MOUSE key)
    {
        if (mousestate[static_cast<int>(key)] == true)
            return true;

        else return false;
    }
    bool InputHandler::IsMouseTriggered(MOUSE key)
    {
        if (mousestate[static_cast<int>(key)] == true && prevmousestate[static_cast<int>(key)] == false)
        {

            return true;
        }

        else return false;
    }
    bool InputHandler::IsMouseReleased(MOUSE key)
    {
        if (mousestate[static_cast<int>(key)] == false && prevmousestate[static_cast<int>(key)] == true)
        {

            return true;
        }

        else return false;
    }
}//JZEngine