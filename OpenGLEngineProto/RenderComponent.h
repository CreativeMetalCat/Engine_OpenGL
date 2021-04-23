#pragma once
#include "Component.h"
namespace Engine::Components
{
	class CRenderComponent :public CComponent
	{
	protected:
		virtual void Draw() = 0;
	public:
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

