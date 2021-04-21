#pragma once
/*Types.h
* this file creates typedefs for mosts of the c++ types that can and might get replaced by other defenitions
* Basic types(like int, bool, float) are not renamed
* This will be filled as time goes
*/
#ifdef USE_DEFAULT_CPP
#include <glm/glm.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

typedef glm::vec3 Vector;

typedef glm::vec2 Vector2;

typedef std::string String;

#endif // USE_DEFAULT_CPP
