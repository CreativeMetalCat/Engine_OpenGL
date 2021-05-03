#include "StaticMeshComponent.h"

#include "Actor.h"
#include "Game.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//class Engine::CActor;

void Engine::Components::CStaticMeshComponent::construct(String materialName,String shaderName)
{
	if (Owner)
	{
		if (Shader* sh = Owner->GetWorld()->game->GetShader(shaderName))
		{
			shader = *sh;
		}
		material = Owner->GetWorld()->game->GetMaterial(materialName);
	}
	if (!mesh.Data.Verticies.empty())
	{
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.Data.Verticies.size(), &mesh.Data.Verticies[0], GL_STATIC_DRAW);
	}
	else
	{
		printf("Error:Mesh is null! Object: %s", Name.c_str());
	}

	if (!mesh.Data.Normals.empty())
	{
		glGenBuffers(1, &normalsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.Data.Normals.size(), &mesh.Data.Normals[0], GL_STATIC_DRAW);
	}
	else
	{
		printf("Error:Mesh has no normals data! Object: %s", Name.c_str());
	}

	if (!mesh.Data.UVs.empty())
	{
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.Data.UVs.size(), &mesh.Data.UVs[0], GL_STATIC_DRAW);
	}
	else
	{
		printf("Error:Mesh has no uv data! Object: %s", Name.c_str());
	}
	

	modelViewPerspectiveMatrixId = glGetUniformLocation(shader.ProgramId, "mvp");
	if (modelViewPerspectiveMatrixId == (uint)(Index_None))
	{
		printf("Shader Warning: Failed to find uniform location for MVP. Shader: %s. Component: %s \n", shader.Name.c_str(), Name.c_str());
	}
	modelMatrixId = glGetUniformLocation(shader.ProgramId, "model");
	viewMatrixId = glGetUniformLocation(shader.ProgramId, "view");
	shader_AmbientLightColorId = glGetUniformLocation(shader.ProgramId, "ambient_light_color");
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnableVertexAttribArray(0);
	//glBindVertexArray(vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,                  // attribute  must match the layout in the shader.
		3,                  // size: x+y+z=3
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glBindVertexArray(0);

	if (!mesh.Data.UVs.empty())
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute. must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glBindVertexArray(1);
	}

	if (!mesh.Data.Normals.empty())
	{
		// 2nd attribute buffer : Normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		glVertexAttribPointer(
			2,                                // attribute.  must match the layout in the shader.
			3,                                // size : x+y+z=3
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glBindVertexArray(2);
	}
}

glm::mat4 Engine::Components::CStaticMeshComponent::getModelMatrix() const
{
	glm::mat4 model = glm::mat4(1);
	
	model = glm::scale(model, Scale);

	model = glm::rotate(model, glm::radians((float)Rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians((float)Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians((float)Rotation.z), glm::vec3(0, 0, 1));
	model = glm::translate(model, Location);

	return model;
}

Shader Engine::Components::CStaticMeshComponent::GetShader() const
{
	return shader;
}

Engine::Components::CStaticMeshComponent::CStaticMeshComponent(String name, CActor* owner,String materialName, LoadedMeshData _mesh, String shaderName, Vector Location, Vector Rotation, Vector Scale)
	:Components::CRenderComponent(name,owner,Location,Rotation,Scale),mesh(_mesh)
{
	construct(materialName,shaderName);
}

void Engine::Components::CStaticMeshComponent::EndDraw()
{
	glBindVertexArray(VertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, mesh.Data.Verticies.size());
	glBindVertexArray(0);

	if (!mesh.Data.UVs.empty())
	{
		glBindVertexArray(1);
	}
	if (!mesh.Data.Normals.empty())
	{
		glBindVertexArray(2);
	}
}

void Engine::Components::CStaticMeshComponent::BeingDraw()
{
	RenderData data = Owner->GetWorld()->game->GetCurrentRenderData();

	glUseProgram(shader.ProgramId);

	glUniformMatrix4fv(modelViewPerspectiveMatrixId, 1, GL_FALSE, glm::value_ptr(data.CameraPerspective * data.CameraView * getModelMatrix()));
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(data.CameraView));
	glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));

	glUniform3f(shader_AmbientLightColorId, data.AmbientLightColor.r, data.AmbientLightColor.b, data.AmbientLightColor.g);

	if (material && material != new Material::Material({}))
	{
		material->Apply(shader.ProgramId);
	}
}

Engine::Components::CStaticMeshComponent::~CStaticMeshComponent()
{
	delete material;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &normalsBuffer);

	shader.~Shader();
}
