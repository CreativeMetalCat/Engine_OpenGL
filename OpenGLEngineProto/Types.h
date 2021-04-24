#pragma once
/*Types.h
* this file creates typedefs for mosts of the c++ types that can and might get replaced by other defenitions or just replaced with shorter names
* Basic types(like int, bool, float) are not renamed
* This will be filled as time goes
*/
#ifdef USE_DEFAULT_CPP
#endif // USE_DEFAULT_CPP
#include <glm/glm.hpp>
#include <iostream>
//#include <GLFW/glfw3.h>
#include <vector>



//Vector of 3 float variables
typedef glm::vec3 Vector;

//Vector of 2 float variables
typedef glm::vec2 Vector2;

typedef glm::vec3 Color;

typedef std::string String;

typedef unsigned int  uint;

template<class Type> 
using Array = std::vector<Type>;

template <class Type1,class Type2>
using Map = std::vector<std::pair<Type1, Type2>>;


enum Constants
{
	Index_None  = -1
};

#define INDEX_NONE Contstants::Index_None