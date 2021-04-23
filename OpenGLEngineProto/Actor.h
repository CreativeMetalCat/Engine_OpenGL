#pragma once
#include "Object.h"
#include "Component.h"

#include "World.h"
class CWorld;

namespace Engine
{
	class CActor :public CObject
	{
		GENERATED_CLASS_BODY(Actor,Object,Engine)
			
	protected:
		Array<CComponent*> components  = Array<CComponent*>();
		
		/*World in which actor exists*/
		CWorld* world;
	public:
		CActor* Owner = nullptr;

		CWorld* GetWorld()const { return world; }

		Array<CActor*>Children = Array<CActor*>();

		Vector Location;

		Vector Rotation;

		Vector Scale;
		
		CActor(String name, CWorld* world, CActor* owner = nullptr);

		CActor(String name, CWorld* world, Vector Location, Vector Rotation, CActor* owner = nullptr);

		//Creates and saves a component
		template<class Class, class ... Args> Class* AddComponent(String name, Args...args);

		// Inherited via CObject
		virtual void Init() override;

		virtual void Update(float deltaTime);
	};
	
}

