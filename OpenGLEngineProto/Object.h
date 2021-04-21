#pragma once
//tell engine to use default(more or less) c++ types
//for example -> std::string for string and glm::vec3 as vector
#define USE_DEFAULT_CPP

#include "Types.h"

namespace Engine
{
	class CObject
	{
	public:
		String Name;

		virtual void Update(float deltaTime) {}

		CObject(String name) :Name(name) {}
	};
}

