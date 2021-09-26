/*                                                                   includes
----------------------------------------------------------------------------- */
#include "PCH.h"
#include "Input.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
namespace JZEngine
{
    /*                                                   objects with file scope
    ----------------------------------------------------------------------------- */
    // static data members declared in GLHelper
    std::unordered_map<int, int> InputHandler::keystate;
    std::unordered_map<int, int> InputHandler::mousestate;


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
        keystate[key] = action;
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
        mousestate[button] = action;
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
#ifdef _DEBUG
        //std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
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
#ifdef _DEBUG
        std::cout << "Mouse scroll wheel offset: ("
            << xoffset << ", " << yoffset << ")" << std::endl;
#endif
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
        std::cerr << "GLFW error: " << description << std::endl;
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
        std::cout << "fbsize_cb getting called!!!" << std::endl;
       
    }

    bool InputHandler::IsKeyPressed(KEY key) 
    {
        if (keystate[static_cast<int>(key)] == GLFW_REPEAT)
            return true;

        else return false;
    }
    bool InputHandler::IsKeyTriggered(KEY key)
    {
        if (keystate[static_cast<int>(key)] == GLFW_PRESS)
        {
            keystate[static_cast<int>(key)] = -1;
            return true;
        }

        else return false;
    }
    bool InputHandler::IsKeyReleased(KEY key)
    {
        if (keystate[static_cast<int>(key)] == GLFW_RELEASE)
        {
            keystate[static_cast<int>(key)] = -1;
            return true;
        }

        else return false;
    }


    bool InputHandler::IsMouseTriggered(MOUSE key)
    {
        if (mousestate[static_cast<int>(key)] == GLFW_PRESS)
        {
            mousestate[static_cast<int>(key)] = -1;
            return true;
        }

        else return false;
    }
    bool InputHandler::IsMouseReleased(MOUSE key)
    {
        if (mousestate[static_cast<int>(key)] == GLFW_RELEASE)
        {
            mousestate[static_cast<int>(key)] = -1;
            return true;
        }

        else return false;
    }

}//JZEngine