#include "Actor.h"
#include "RenderComponent.h"
#include "World.h"

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

Engine::CActor::CActor(String name, CWorld* _world,  CActor* _owner,Vector location, Vector rotation)
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
	if (!components.empty())
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->Update(deltaTime);

			if (components[i]->GetClass().Category == "RenderComponents")
			{
				Components::CRenderComponent* temp = static_cast<Components::CRenderComponent*>(components[i]);
				temp->BeingDraw();
				OnComponentDraw(temp);
				temp->EndDraw();
			}
		}
	}
}

void Engine::CActor::OnComponentDraw(Components::CRenderComponent* comp)
{
}
