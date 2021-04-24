#include "StaticMeshComponent.h"

#include "Actor.h"
#include "Game.h"


//class Engine::CActor;

Shader Engine::Components::CStaticMeshComponent::GetShader() const
{
	return shader;
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

void Engine::Components::CStaticMeshComponent::EndDraw()
{
}

void Engine::Components::CStaticMeshComponent::BeingDraw()
{
	Owner->GetWorld()->GetCurrentRenderData();
}
