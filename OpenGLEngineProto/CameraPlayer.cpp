#include "CameraPlayer.hpp"


CCameraPlayer::CCameraPlayer(GLFWwindow* _window, glm::vec3 location, float fov, float movementSpeed, float mouseSpeed)
	:window(_window),FOV(fov),MovementSpeed(movementSpeed),MouseSpeed(mouseSpeed)
{

}

void CCameraPlayer::UpdateMouse(float deltaTime)

{//Mouse coords relative to the screen
	GLdouble xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	GLint width, height;
	glfwGetWindowSize(window, &width, &height);

	Rotation.x += MouseSpeed * deltaTime * float(1024 / 2 - xPos);
	Rotation.y += MouseSpeed * deltaTime * float(768 / 2 - yPos);

	glfwSetCursorPos(window, width / 2, height / 2);
}

void CCameraPlayer::UpdatePosition(float deltaTime)
{
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
	{
		Location += GetForwardVector() * deltaTime * MovementSpeed;
	}
	// Move backward

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		Location -= GetForwardVector() * deltaTime * MovementSpeed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
	{
		Location += GetRightVector() * deltaTime * MovementSpeed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
	{
		Location -= GetRightVector() * deltaTime * MovementSpeed;
	}
}

void CCameraPlayer::Update(float deltaTime)
{
	UpdateMouse(deltaTime);
	UpdatePosition(deltaTime);
}

glm::vec3 CCameraPlayer::GetForwardVector() const
{
	return glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		sin(Rotation.y),
		cos(Rotation.y) * cos(Rotation.x)
	);
}

glm::vec3 CCameraPlayer::GetRightVector() const
{
	return glm::vec3(
		sin(Rotation.x - 3.14f / 2.0f),
		0,
		cos(Rotation.x - 3.14f / 2.0f)
	);
}

glm::mat4 CCameraPlayer::GetViewMatrix() const
{
	// Camera matrix
	return glm::lookAt(
		Location,           // Camera is here
		Location + GetForwardVector(), // and looks here : at the same position, plus "direction"
		glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

glm::mat4 CCameraPlayer::GetPerspective() const
{
	return glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
}
