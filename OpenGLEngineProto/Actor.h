#pragma once
#include "Object.h"
#include "Component.h"

namespace Engine
{
	class CActor :public Engine::CObject
	{
	protected:
		Array<CComponent*> components = Array<CComponent*>();

		CActor* owner = nullptr;
	public:
		CActor* GetOwner()const { return owner; }

		Vector Location;

		Vector Rotation;
		
		CActor(String name, CActor* owner = nullptr);

		CActor(String name, Vector Location, Vector Rotation, CActor* owner = nullptr);

		//Creates and saves a component
		template<class Class, class ... Args> Class* AddComponent(String name, Args...args);
	};
	
}

