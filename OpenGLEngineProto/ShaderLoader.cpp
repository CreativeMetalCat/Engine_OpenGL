#include "ShaderLoader.hpp"
#include <GL/glew.h>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "Macros.h"
GLuint Helpers::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) 
{
	//Create shaders for output
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. AAA!\n", vertex_file_path);
		getchar();
		//it should fall back to some built-in shader that is just black and pink squares
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = vertexShaderCode.c_str();

	//we load shader into vertexShaderId
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	//we compile loaded shader
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	//link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

uint Helpers::LoadShaders(String vertText, String fragText)
{
	//Create shaders for output
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int InfoLogLength;

	char const* VertexSourcePointer = vertText.c_str();

	//we load shader into vertexShaderId
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	//we compile loaded shader
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	char const* FragmentSourcePointer = fragText.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	//link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	LOG_ERROR(glewGetErrorString(err), glGetError(), Helpers::LoadShaders(String vertText, String fragText), "Static Shader Loader");
	return ProgramID;
}

std::pair<String, String> Helpers::LoadShaderText(String filepath, ShaderPathMode mode)
{

	std::string vertexShaderCode;
	std::ifstream VertexShaderStream(std::string(filepath + (mode == ShaderPathMode::Extension ? ".vs" : "Vertex.glsl")).c_str(), std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		printf("Fatal error! Failed to open %s Make sure they are in the right folder \n", std::string(filepath + (mode == ShaderPathMode::Extension ? ".vs" : "Vertex.glsl")).c_str());
		getchar();
		//it should fall back to some built-in shader that is just black and pink squares
		return std::pair<String, String>();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(std::string(filepath + (mode == ShaderPathMode::Extension ? ".fs" : "Fragment.glsl")).c_str(), std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	return std::pair<String, String>(vertexShaderCode, FragmentShaderCode);
}
