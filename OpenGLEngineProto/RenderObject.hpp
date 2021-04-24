#pragma once


#include <vector>

#include "ShaderLoader.hpp"
#include "Mesh.h"
#include "Light.h"



struct RenderData
{
public:
	glm::mat4 CameraPerspective;

	glm::mat4 CameraView;

	std::vector<Light> lights;
};

#if 0
class /*[[deprecated("RenderObject is deprecated and is replaced by StaticMeshComponent")]]*/  CRenderObject
{
protected:

	GLuint TEST_diffuse_intensityId;
	GLuint TEST_diffuse_reflectivityId;
	GLuint TEST_diffuse_posId;

	//id of ambient_light_intensity
	GLuint aliId;

	//id of ambient_light_reflectivity
	GLuint alrId;

	GLuint vertexBuffer;

	GLuint normalBuffer;

	GLuint uvBuffer;

	GLuint matrixId;

	GLuint modelMatrixId;

	GLuint viewMatrixId;

	GLuint texture;

	GLuint textureId;
public:
	float sky_light_refl = 0.5;

	float sky_light_intensity = 0.3f;

	float test_light_intensity = 0;

	glm::vec3 Location = glm::vec3(0);
	
	glm::vec3 Rotation = glm::vec3(1);

	glm::vec3 Scale = glm::vec3(1);

	glm::vec3 TEST_LIGHT_POS = glm::vec3(0);

	MeshData Mesh;

	std::string ShaderName;

	std::string TextureName;

	GLint shaderProgramId;

	bool ShouldUpdate = true;

	CRenderObject(MeshData mesh,std::string textureName, std::string shaderName);

	virtual void Draw(RenderData data);

	glm::mat4 GetModelMatrix()const;

	virtual void Update(float deltaTime);

	~CRenderObject()
	{
		// Cleanup VBO and shader
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteProgram(shaderProgramId);

		Mesh.~MeshData();
	}
};
#endif