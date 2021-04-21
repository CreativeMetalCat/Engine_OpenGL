#include "RenderObject.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CRenderObject::CRenderObject(MeshData mesh,std::string textureName, std::string shaderName)
	:Mesh(mesh), TextureName(textureName), ShaderName(shaderName)
{
	shaderProgramId = Helpers::LoadShaders((std::string("Shaders/") + shaderName + std::string("Vertex.glsl")).c_str(), (std::string("Shaders/") + shaderName + std::string("Fragment.glsl")).c_str());

	if (!Mesh.Verticies.empty())
	{
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.Verticies.size(), &mesh.Verticies[0], GL_STATIC_DRAW);
	}
	else
	{
		printf("Given mesh is null");
	}

	if (!Mesh.Normals.empty())
	{
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Mesh.Normals.size(), &Mesh.Normals[0], GL_STATIC_DRAW);
	}

	if (!Mesh.UVs.empty())
	{
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.UVs.size(), &mesh.UVs[0], GL_STATIC_DRAW);
	}
	else
	{
		printf("Mesh has no uv data!");
	}

	int height;//image height
	int width;//image width
	int comp;//channels

	unsigned char* image = stbi_load(TextureName.c_str(), &height, &width, &comp, STBI_rgb_alpha);
	if (image == nullptr)
	{
		//fallback to using null checkboard(not yet implemented)
		printf("Failed to load a texure. %s", TextureName.c_str());
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	//remove the image -> we don't need it anymore
	delete[] image;

	matrixId = glGetUniformLocation(shaderProgramId, "mvp");
	modelMatrixId = glGetUniformLocation(shaderProgramId, "model");
	viewMatrixId = glGetUniformLocation(shaderProgramId, "view");

	textureId = glGetUniformLocation(shaderProgramId, "textureSampler");
	aliId = glGetUniformLocation(shaderProgramId, "ambient_light_intensity");
	alrId = glGetUniformLocation(shaderProgramId, "ambient_light_reflectivity");
}

void CRenderObject::Draw(RenderData data)
{
	glUseProgram(shaderProgramId);

	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(data.CameraPerspective * data.CameraView * GetModelMatrix()));
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(data.CameraView));
	glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));

	glUniform1f(aliId, sky_light_intensity);
	glUniform1f(alrId, sky_light_refl);

	glUniform3f(TEST_diffuse_posId, TEST_LIGHT_POS.x, TEST_LIGHT_POS.y, TEST_LIGHT_POS.z);
	
	glUniform1f(TEST_diffuse_intensityId, 1);
	glUniform1f(TEST_diffuse_reflectivityId, test_light_intensity);

	if (!data.lights.empty())
	{
		GLint i = 0;
		for (auto it = data.lights.begin(); it != data.lights.end(); ++it)
		{
			std::string number = std::to_string(i).c_str();
			glUniform1i(glGetUniformLocation(shaderProgramId, ("pointLights[" + number + "].Exists").c_str()), (int)(!(*it).Fake));

			//there is no point in setting other variables because shader code will ignore them
			/*
			* shader code:
			if(!light.Exists)
			{
				return vec3(0,0,0);
			}
			*/
			if (!(*it).Fake)
			{
				//load location
				glUniform3f(glGetUniformLocation(shaderProgramId, ("pointLights[" + number + "].Location").c_str()), (*it).Location.x, (*it).Location.y, (*it).Location.z);

				glUniform3f(glGetUniformLocation(shaderProgramId, ("pointLights[" + number + "].Color").c_str()), (*it).Color.x, (*it).Color.y, (*it).Color.z);

				glUniform1f(glGetUniformLocation(shaderProgramId, ("pointLights[" + number + "].Intensity").c_str()), (*it).Intensity);

				glUniform1f(glGetUniformLocation(shaderProgramId, ("pointLights[" + number + "].Reflectivity").c_str()), 1.f);
			}
			i++;
		}
	}

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureId, 0);

	glEnableVertexAttribArray(0);
	//glBindVertexArray(vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	if (!Mesh.UVs.empty())
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}
	if (!Mesh.Normals.empty())
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}

	// Draw the triangle !
	glDrawArrays(Mesh.QuadMesh? GL_POINTS :GL_TRIANGLES, 0, Mesh.Verticies.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

glm::mat4 CRenderObject::GetModelMatrix() const
{
	glm::mat4 model = glm::mat4(1);
	model = glm::scale(model, Scale);
	
	model = glm::rotate(model, glm::radians((float)Rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians((float)Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians((float)Rotation.z), glm::vec3(0, 0, 1));
	model = glm::translate(model, Location);
	
	
	return model;
}

void CRenderObject::Update(float deltaTime)
{
	
}
