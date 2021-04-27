#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>

void Engine::Components::Camera::CCameraComponent::Init()
{
}

Matrix Engine::Components::Camera::CCameraComponent::GetPerspective() const
{
    return glm::perspective(glm::radians(FoV), 4.0f / 3.0f, NearClipPlane, FarClipPlane);
}

Matrix Engine::Components::Camera::CCameraComponent::GetViewMatrix() const
{
    return Matrix();
}
