#include "RenderComponent.h"
#include "Actor.h"

Vector Engine::Components::CRenderComponent::GetWorldLocation() const
{
	return Owner->GetWorldLocation() + Location;
}

Vector Engine::Components::CRenderComponent::GetWorldRotation() const
{
	return Owner->GetWorldRotation() + Rotation;
}

Engine::Components::CRenderComponent::CRenderComponent(String name, CActor* owner, Vector location, Vector rotation, Vector scale)
	:CComponent(name,owner), Location(location), Rotation(rotation),Scale(scale)
{
	set_class_data_generated();
}

Engine::Components::CRenderComponent::CRenderComponent(String name, CActor* owner)
	:CComponent(name, owner)
{
	set_class_data_generated();
}

void Engine::Components::CRenderComponent::Update(float deltaTime)
{
	
}

void Engine::Components::CRenderComponent::Init()
{
}
