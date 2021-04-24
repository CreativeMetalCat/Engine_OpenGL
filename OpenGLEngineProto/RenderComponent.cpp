#include "RenderComponent.h"

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
