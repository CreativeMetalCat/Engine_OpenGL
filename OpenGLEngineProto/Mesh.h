#pragma once
#define USE_DEFAULT_CPP
#include "Types.h"

struct MeshData
{
	Array<float>Verticies;

	Array<float>UVs;

	Array<float> Normals;

	bool QuadMesh = false;

	MeshData(std::vector<float>verticies, std::vector<float>_UVs)
		:Verticies(verticies), UVs(_UVs)
	{

	}

	MeshData() {}

	~MeshData()
	{
		Verticies.~vector();
		UVs.~vector();
	}
};