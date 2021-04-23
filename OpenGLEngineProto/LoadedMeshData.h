#pragma once

#include "Mesh.h"

struct LoadedMeshData
{
	MeshData Data;

	Vector RelativeLocation;

	Vector RelativeRotation;

	float Scale = 1;

	Array<String> MaterialNames;
};