#pragma once

#define USE_DEFAULT_CPP
#include "Types.h"
#include "LightData.h"

/*
* This struct passes data needed for rendering
* Camera data, Light info, etc.
*/
struct RenderData
{
public:
	glm::mat4 CameraPerspective;

	glm::mat4 CameraView;

	Array<LightData> Lights = Array<LightData>();
};