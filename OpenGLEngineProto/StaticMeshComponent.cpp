#include "StaticMeshComponent.h"

#include "Actor.h"

//class Engine::CActor;

void Engine::Components::CStaticMeshComponent::Draw()
{
	Owner->GetWorld()->GetCurrentRenderData();
}