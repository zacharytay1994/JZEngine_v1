/*	__FILE HEADER__
*	File:		DeltaTime.h
    Primary:	Deon Khong
    Date:		26/08/21
    Brief:		Measures delta time.
*/

#pragma once

#include <GLFW/glfw3.h>

namespace JZEngine {

    class DeltaTime {

        static inline double  FPS;
        static inline double  delta_time;

    public:
        static double get_FPS()
        {
            return FPS;
        }
        static double get_deltatime()
        {
            return delta_time;
        }
        static void update_deltatime(double fps_calc_interval) {
            // get elapsed time (in seconds) between previous and current frames
            static double prev_time = glfwGetTime();
            double curr_time = glfwGetTime();
            delta_time = curr_time - prev_time;
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
                FPS = count / elapsed_time;
                start_time = curr_time;
                count = 0.0;
            }
            // done calculating fps ...
            
        }

    };
}//JZEngine