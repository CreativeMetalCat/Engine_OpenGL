#pragma once
#include "RenderComponent.h"
namespace Engine::Components::Camera
{
	class CCameraComponent: public CRenderComponent
	{
		GENERATED_CLASS_BODY(CameraComponent,RenderComponent,Camera, Engine::Components)
	public:
		CCameraComponent(String name, CActor* owner, float fov, float near = 0.1f, float far = 100.f, Vector Location = Vector(1), Vector Rotation = Vector(1), Vector Scale = Vector(1));

		float FoV = 60.f;

		float NearClipPlane = 0.1f;

		float FarClipPlane = 100.f;

		// Inherited via CComponent
		virtual void Init() override;

		Matrix GetPerspective()const;

		Matrix GetViewMatrix() const;
	};
}

