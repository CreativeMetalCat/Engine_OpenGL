#pragma once
#include "Actor.h"
#include "RenderData.h"

namespace Engine
{
	class CWorld
	{
	protected:
		Array<CActor*> actors = Array<CActor*>();

		RenderData currentRenderData;
	public:
		RenderData GetCurrentRenderData()const { return currentRenderData; }

		Array<CActor*> GetActorsOfClass(String className);

		template<class Class, class ... Args> Class* SpawnActor(String name,CActor*owner = nullptr, Args ... args);

		virtual void Update(float deltaTime);

		virtual void Init();

		~CWorld();
	};
}

