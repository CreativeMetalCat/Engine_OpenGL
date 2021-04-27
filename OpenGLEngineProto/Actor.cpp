#include "Actor.h"
#include "RenderComponent.h"
#include "World.h"


Vector Engine::CActor::GetForwardVector() const
{
	return glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		sin(Rotation.y),
		cos(Rotation.y) * cos(Rotation.x)
	);
}

Vector Engine::CActor::GetRightVector() const
{
	return glm::vec3(
		sin(Rotation.x - 3.14f / 2.0f),
		0,
		cos(Rotation.x - 3.14f / 2.0f)
	);
}

Vector Engine::CActor::GetWorldLocation() const
{
	if (Owner)
	{
		return Owner->GetWorldLocation() + Location;
	}
	else
	{
		return Location;
	}
}

Vector Engine::CActor::GetWorldRotation() const
{
	if (Owner)
	{
		return Owner->GetWorldRotation() + Rotation;
	}
	else
	{
		return Rotation;
	}
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
