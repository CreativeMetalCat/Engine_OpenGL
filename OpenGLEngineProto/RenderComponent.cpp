#include "RenderComponent.h"

Engine::Components::CRenderComponent::CRenderComponent(String name, CActor* owner, Vector location, Vector rotation, Vector scale)
	:CComponent(name,owner), Location(location), Rotation(rotation),Scale(scale)
{
	classInfo.Name = "RenderComponent";
	classInfo.Parent = "Component";
}

Engine::Components::CRenderComponent::CRenderComponent(String name, CActor* owner)
	:CComponent(name, owner)
{
	classInfo.Name = "RenderComponent";
	classInfo.Parent = "Component";
}

void Engine::Components::CRenderComponent::Update(float deltaTime)
{
	Draw();
}

void Engine::Components::CRenderComponent::Init()
{
}
