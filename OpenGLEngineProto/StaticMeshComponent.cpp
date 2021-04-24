#include "StaticMeshComponent.h"

#include "Actor.h"
#include "Game.h"


//class Engine::CActor;

Shader Engine::Components::CStaticMeshComponent::GetShader() const
{
	return shader;
}

void Engine::Components::CStaticMeshComponent::Draw()
{
	Owner->GetWorld()->GetCurrentRenderData();
}

Engine::Components::CStaticMeshComponent::CStaticMeshComponent(String shaderName, String name, CActor* owner, Vector Location, Vector Rotation, Vector Scale)
	:Components::CRenderComponent(name,owner,Location,Rotation,Scale)
{
	if (owner)
	{
		if (Shader* sh = owner->GetWorld()->game->GetShader(shaderName))
		{
			shader = *sh;
		}
	}
}

Engine::Components::CStaticMeshComponent::CStaticMeshComponent(String shaderName, String name, CActor* owner)
	:Components::CRenderComponent(name, owner)
{
	if (owner)
	{
		if (Shader* sh = owner->GetWorld()->game->GetShader(shaderName))
		{
			shader = *sh;
		}
	}
}
