/*!
@file    glhelper.cpp
@author  pghali@digipen.edu
@date    10/11/2016

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and use GLEW to extract function
pointers to OpenGL implementations.

*//*__________________________________________________________________________*/

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

    GLdouble InputHandler::fps;

    std::unordered_map<int, GLboolean> InputHandler::keystate;
    std::unordered_map<int, GLboolean> InputHandler::mousestate;

    /*  _________________________________________________________________________ */
    /*! init

    @param GLint width
    @param GLint height
    Dimensions of window requested by program

    @param std::string title_str
    String printed to window's title bar

    @return bool
    true if OpenGL context and GLEW were successfully initialized.
    false otherwise.

    Uses GLFW to create OpenGL context. GLFW's initialization follows from here:
    http://www.glfw.org/docs/latest/quick.html
    a window of size width x height pixels
    and its associated OpenGL context that matches a core profile that is
    compatible with OpenGL 4.5 and doesn't support "old" OpenGL, has 32-bit RGBA,
    double-buffered color buffer, 24-bit depth buffer and 8-bit stencil buffer
    with each buffer of size width x height pixels
    */
    bool InputHandler::init(GLFWwindow* ptr) {

        
        
        glfwSetKeyCallback(ptr, InputHandler::key_cb);
        glfwSetMouseButtonCallback(ptr, InputHandler::mousebutton_cb);
        glfwSetCursorPosCallback(ptr, InputHandler::mousepos_cb);
        glfwSetScrollCallback(ptr, InputHandler::mousescroll_cb);
        glfwSetInputMode(ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return true;
    }

    /*  _________________________________________________________________________ */
    /*! cleanup

    @param none

    @return none

    For now, there are no resources allocated by the application program.
    The only task is to have GLFW return resources back to the system and
    gracefully terminate.
    */
    void InputHandler::cleanup() {
        // Part 1
        glfwTerminate();
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
        if (GLFW_PRESS == action)
        {
            if (GLFW_KEY_ESCAPE == key)
            {
                glfwSetWindowShouldClose(pwin, GLFW_TRUE);
            }
            keystate[key] = GL_TRUE;

            std::cout << "key press :" << key << "\n";

        }
        else if (GLFW_REPEAT == action)
        {

            keystate[key] = GL_TRUE;


        }
        else if (GLFW_RELEASE == action)
        {
            keystate[key] = GL_FALSE;

        }


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

        if (GLFW_PRESS == action) {

            mousestate[button] = GL_TRUE;
            std::cout << "mouse press" << "\n";

        }
        else if (GLFW_REPEAT == action) {
            // key state was and is being pressed
            mousestate[button] = GL_FALSE;


        }
        else if (GLFW_RELEASE == action) {
            // key start changes from pressed to released
            mousestate[button] = GL_FALSE;

        }
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

    /*  _________________________________________________________________________*/
    /*! update_time

    @param double&
    fps: computed frames per second

    @param double
    fps_calc_interval: the interval (in seconds) at which fps is to be
    calculated

    @return double
    Return time interval (in seconds) between previous and current frames

    This function is first called in init() and once each game loop by update().
    It uses GLFW's time functions to:
    1. compute interval in seconds between each frame
    2. compute the frames per second every "fps_calc_interval" seconds
    */
    double InputHandler::update_time(double fps_calc_interval) {
        // get elapsed time (in seconds) between previous and current frames
        static double prev_time = glfwGetTime();
        double curr_time = glfwGetTime();
        double delta_time = curr_time - prev_time;
        prev_time = curr_time;

        // fps calculations
        static double count = 0.0; // number of game loop iterations
        static double start_time = glfwGetTime();
        // get elapsed time since very beginning (in seconds) ...
        double elapsed_time = curr_time - start_time;

        ++count;

        // update fps at least every 10 seconds ...
        fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
        fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
        if (elapsed_time > fps_calc_interval) {
            InputHandler::fps = count / elapsed_time;
            start_time = curr_time;
            count = 0.0;
        }

        // done calculating fps ...
        return delta_time;
    }

    bool InputHandler::IsKeyPressed(KEY key) 
    {
        return keystate[static_cast<int>(key)];
    }

    bool InputHandler::IsMousePressed(MOUSEBUTTON key) 
    {
        return mousestate[static_cast<int>(key)];
    }

}//JZEngine