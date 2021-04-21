#pragma once
#include <vector>
#include <GL/glew.h>

struct MeshData
{
	std::vector<GLfloat>Verticies;

	std::vector<GLfloat>UVs;

	std::vector<GLfloat> Normals;

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