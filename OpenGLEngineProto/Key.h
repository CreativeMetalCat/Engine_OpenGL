#pragma once

#include <GLFW/glfw3.h>

namespace Engine::Key
{
	enum KeyState
	{
		Released = GLFW_RELEASE,
		Pressed = GLFW_PRESS,
		Repeated = GLFW_REPEAT
	};
}