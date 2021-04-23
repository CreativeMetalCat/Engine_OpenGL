#pragma once
#define USE_DEFAULT_CPP
#include "Types.h"

struct MeshData
{
	Array<GLfloat>Verticies;

	Array<GLfloat>UVs;

	Array<GLfloat> Normals;

	bool QuadMesh = false;

	MeshData(std::vector<GLfloat>verticies, std::vector<GLfloat>_UVs)
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