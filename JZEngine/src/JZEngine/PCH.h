#pragma once

#define UNREFERENCED_PARAMETER(P)(P)

/*
Be sure to include GLAD before GLFW. The include file for GLAD includes
the required OpenGL headers behind the scenes (like GL/gl.h) so be sure
to include GLAD before other header files that require OpenGL (like GLFW).
*/

// containers
#include <string>
#include <array>
#include <vector>
#include <queue>

// streams
#include <fstream>
#include <sstream>
#include <iostream>

#include <memory.h>
#include <type_traits>
#include <typeinfo>
#include <math.h>
#include <chrono>
