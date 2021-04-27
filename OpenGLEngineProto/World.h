#pragma once

#include "Actor.h"
#include "RenderData.h"


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

	template<class Class, class ... Args>
	inline Class* CWorld::SpawnActor(String name, CActor* owner, Args ... args)
	{
		Class* actor = new Class(name, this, owner, args...);
		if (actor)
		{
			actors.push_back(actor);
			return actor;
		}
		return NULL;

	}
}

