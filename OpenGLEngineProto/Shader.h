#pragma once
#include <GL/glew.h>
#define USE_DEFAULT_CPP
#include "Types.h"


/*Representaion of OpenGL's shaders in a bit more easy to use way*/
struct Shader
{
	/*id of shader "program", used in opengl function*/
	uint ProgramId = 0;
	/*Name of the shader, used for search*/
	String Name = "null";

	Shader(uint programId, String name) :ProgramId(programId), Name(name) {}

	Shader() {}

	~Shader()
	{
		glDeleteProgram(ProgramId);
	}
};