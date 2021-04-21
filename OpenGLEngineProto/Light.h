#pragma once
#include "glm/glm.hpp"


//a simple omnidirectional light
class Light
{
public:
	glm::vec3 Location;

	float Intensity;

	float Attenuetion;

	glm::vec3 Color;

	bool Fake = true;

	Light(glm::vec3 location, float intensity, float attenuetion, glm::vec3 color)
		:Location(location),Intensity(intensity),Attenuetion(attenuetion),Color(color)
	{

	}
};

//light that doesn't have a position -> basically makes world have this color
//can only be one light per world
class AmbientLight
{
	glm::vec3 Color;

	float Intensity;
};

