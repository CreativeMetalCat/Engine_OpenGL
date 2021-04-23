#include "Actor.h"

template<class Class, class ...Args>
inline Class* Engine::CActor::AddComponent(String name, Args ...args)
{
	
	Class* comp = new Class(name, args);
	if (comp)
	{
		components.push_back(comp);
		return comp;
	}
	return NULL;
}

Engine::CActor::CActor(String name, CWorld* _world, CActor* _owner):CObject(name), Owner(_owner),world(_world)
{
	set_class_data_generated();
}

Engine::CActor::CActor(String name, CWorld* _world, Vector location, Vector rotation, CActor* _owner)
	: CObject(name), Location(location),Rotation(rotation), Owner(_owner), world(_world)
{
	set_class_data_generated();
}

void Engine::CActor::Init()
{
	if (!components.empty())
	{
		for (int i = 0; i < components.size(); i++) 
		{
			components[i]->Init();
		}
	}
}

void Engine::CActor::Update(float deltaTime)
{
	Super::Update(deltaTime);
	world->GetActorsOfClass(classInfo.Name);
}
