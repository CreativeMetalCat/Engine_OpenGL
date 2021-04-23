#pragma once
#include "Actor.h"

namespace Engine
{
	class CWorld
	{
	protected:
		Array<CActor*> actors = Array<CActor*>();

	public:
		template<class Class, class ... Args> Class* SpawnActor(String name,CActor*owner = nullptr, Args ... args);
	};
}

