#pragma once
#include "Component.h"
#include "LoadedMeshData.h"

namespace Engine::Components
{
	class CRenderComponent :public CComponent
	{
		GENERATED_CLASS_BODY(RenderComponent,Component, RenderComponents, Engine)
	protected:
		
	public:
		virtual void BeingDraw() = 0;

		virtual void EndDraw() = 0;

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

