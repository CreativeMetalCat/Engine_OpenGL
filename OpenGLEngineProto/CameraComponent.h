#pragma once
#include "RenderComponent.h"
namespace Engine::Components::Camera
{
	class CCameraComponent: public CRenderComponent
	{
	public:
		float FoV = 60.f;

		float NearClipPlane = 0.1f;

		float FarClipPlane = 100.f;

		// Inherited via CComponent
		virtual void Init() override;

		Matrix GetPerspective()const;

		Matrix GetViewMatrix() const;
	};
}

