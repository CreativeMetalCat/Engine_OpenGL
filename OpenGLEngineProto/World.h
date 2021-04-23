#pragma once
#include "Actor.h"

namespace Engine
{
	class CWorld
	{
	protected:
		Array<CActor*> actors = Array<CActor*>();

	public:
		
		Array<CActor*> GetActorsOfClass(String className);

		template<class Class, class ... Args> Class* SpawnActor(String name,CActor*owner = nullptr, Args ... args);

		virtual void Update(float deltaTime);

		virtual void Init();

		~CWorld();
	};
}

