#pragma once
#include "Actor.h"
#include "RenderData.h"
#include "Shader.h"

namespace Engine
{
	class CGame;

	class CWorld
	{
	protected:
		Array<CActor*> actors = Array<CActor*>();


		RenderData currentRenderData;
	public:
		/*The game itself*/
		CGame* game;

		RenderData GetCurrentRenderData()const { return currentRenderData; }

		Array<CActor*> GetActorsOfClass(String className);

		template<class Class, class ... Args> Class* SpawnActor(String name,CActor*owner = nullptr, Args ... args);

		virtual void Update(float deltaTime);

		virtual void Init();

		~CWorld();
	};
}

