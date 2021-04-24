#pragma once
#include "Component.h"
#include "LoadedMeshData.h"

namespace Engine::Components
{
	class CRenderComponent :public CComponent
	{
		GENERATED_CLASS_BODY(RenderComponent,Component, Engine)
	protected:
		
	public:
		virtual void Draw() = 0;

		Vector Location;

		Vector Rotation;

		Vector Scale;
		
		CRenderComponent(String name, CActor* owner, Vector Location, Vector Rotation, Vector Scale);

		CRenderComponent(String name, CActor* owner);

		void Update(float deltaTime)override;

		// Inherited via CComponent
		virtual void Init() override;
	};
}

