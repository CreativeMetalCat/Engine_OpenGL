#include "CameraComponent.h"
#include "Actor.h"
#include <glm/gtc/matrix_transform.hpp>


Engine::Components::Camera::CCameraComponent::CCameraComponent(String name, CActor* owner, float fov, float near, float far, Vector Location, Vector Rotation, Vector Scale)
	:CRenderComponent(name,owner,Location,Rotation,Scale),FoV(fov),NearClipPlane(near),FarClipPlane(far)
{
}

void Engine::Components::Camera::CCameraComponent::Init()
{
}

Matrix Engine::Components::Camera::CCameraComponent::GetPerspective() const
{
    return glm::perspective(glm::radians(FoV), 4.0f / 3.0f, NearClipPlane, FarClipPlane);
}

Matrix Engine::Components::Camera::CCameraComponent::GetViewMatrix() const
{
	// Camera matrix
	return glm::lookAt(
		GetWorldLocation(),           // Camera is here
		Location + Owner->GetForwardVector(), // and looks here : at the same position, plus "direction"
		glm::vec3(0, 1, 0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}
