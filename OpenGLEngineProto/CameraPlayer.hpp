#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CCameraPlayer
{
protected:
	void UpdateMouse(float deltaTime);

	void UpdatePosition(float deltaTime);
public:

	CCameraPlayer(GLFWwindow* _window, glm::vec3 location, float fov = 60, float movementSpeed = 1, float MouseSpeed = 0.005f);

	GLFWwindow* window;

	glm::vec3 Location;

	glm::vec3 Rotation;

	float FOV = 60;

	float MovementSpeed = 1;

	float MouseSpeed = 0.005f;

	virtual void Update(float deltaTime);

	glm::vec3 GetForwardVector()const;

	glm::vec3 GetRightVector()const;

	glm::mat4 GetViewMatrix()const;

	glm::mat4 GetPerspective()const;
};

