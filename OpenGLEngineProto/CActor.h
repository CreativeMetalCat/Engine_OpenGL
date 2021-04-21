#pragma once
#include "Object.h"

namespace Engine
{
	class CActor :public Engine::CObject
	{
	public:
		Vector Location;

		Vector Rotation;
	};
}

