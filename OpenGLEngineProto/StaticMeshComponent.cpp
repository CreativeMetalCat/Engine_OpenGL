#include "StaticMeshComponent.h"

#include "Actor.h"
#include "Game.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//class Engine::CActor;

void Engine::Components::CStaticMeshComponent::construct(Material::Material* material,String shaderName)
{
	if (Owner)
	{
		if (Shader* sh = Owner->GetWorld()->game->GetShader(shaderName))
		{
			shader = *sh;
		}
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

	modelViewPerspectiveMatrixId = glGetUniformLocation(shaderProgramId, "mvp");
	modelMatrixId = glGetUniformLocation(shaderProgramId, "model");
	viewMatrixId = glGetUniformLocation(shaderProgramId, "view");
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

Engine::Components::CStaticMeshComponent::CStaticMeshComponent(String name, CActor* owner,Material::Material* material, LoadedMeshData _mesh, String shaderName, Vector Location, Vector Rotation, Vector Scale)
	:Components::CRenderComponent(name,owner,Location,Rotation,Scale),mesh(_mesh)
{
	construct(material,shaderName);
}

void Engine::Components::CStaticMeshComponent::EndDraw()
{
	glDrawArrays(GL_TRIANGLES, 0, mesh.Data.Verticies.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
}

void Engine::Components::CStaticMeshComponent::BeingDraw()
{
	RenderData data = Owner->GetWorld()->GetCurrentRenderData();

	glUseProgram(shaderProgramId);

	glUniformMatrix4fv(modelViewPerspectiveMatrixId, 1, GL_FALSE, glm::value_ptr(data.CameraPerspective * data.CameraView * getModelMatrix()));
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(data.CameraView));
	glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));

	if (material)
	{
		material->Apply(shader.ProgramId);
	}

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
	}
	if (!mesh.Data.Normals.empty())
	{
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
