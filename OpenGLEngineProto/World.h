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
	public:
#pragma region AmbientLight
		float AmbientLightIntensity = 1.f;

		Color AmbientLightColor = Color(0);

		bool AmbientLightEnabled = true;
#pragma endregion

		/*The game itself*/
		CGame* game;

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

