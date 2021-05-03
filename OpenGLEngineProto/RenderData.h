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
	Matrix CameraPerspective;

	Matrix CameraView;

	Array<LightData> Lights = Array<LightData>();

	float AmbientLightIntensity = 1.f;

	Color AmbientLightColor = Color(0);
};