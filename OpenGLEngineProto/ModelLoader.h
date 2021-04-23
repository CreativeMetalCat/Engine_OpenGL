#pragma once

#include <vector>
#include <GL/glew.h>
#include <iostream>
#include "LoadedMeshData.h"
#include <glm/glm.hpp>


class ModelLoader
{

protected:

	//actual function that does loading
	//these should be replaced based on whatever libs will be used to avoid breaking old code
	static MeshData LoadModel_tinyOBJ(std::string filepath, float scale);

	static LoadedMeshData LoadModel_openFBX(std::string filepath, float scale);

	static std::vector<LoadedMeshData> LoadModelFromScene_openFBX(std::string filepath, float scale);
public:
	//Loads mesh data from file, only .fbx is currently supported
	static LoadedMeshData LoadModel(std::string filepath,float scale);

	//loads every mesh in the model file as separate mesh.
	//Useful for loading scenes made in other software
	//currently .fbx is supported
	static std::vector<LoadedMeshData> LoadModelFromScene(std::string filepath, float scale);
};



