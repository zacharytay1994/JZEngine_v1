#pragma once

#include <GLFW/glfw3.h>

namespace JZEngine {

    namespace DeltaTime {

        double FPS;

        double update_time(double fps_calc_interval) {
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
                FPS = count / elapsed_time;
                start_time = curr_time;
                count = 0.0;
            }

            // done calculating fps ...
            return delta_time;
        }

    };
}//JZEngine