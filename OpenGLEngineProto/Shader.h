#pragma once
#include <GL/glew.h>
#define USE_DEFAULT_CPP
#include "Types.h"


/*Representaion of OpenGL's shaders in a bit more easy to use way*/
struct Shader
{
	/*for drawing*/
	uint ProgramId = -1;

	/*Name of the shader, used for error display*/
	String Name = "null";
};

/*Struct that contains raw data(the text of shader)
* 
*/
class ShaderRawData
{
protected:
	String VertexShaderText;

	String FragmentShaderText;

public:

	bool Valid = false;

	/*Name of the shader, used for search*/
	String Name = "null";

	ShaderRawData(String vertexShaderText, String fragmentShaderText);

	//filename is relative to shaders folder of the project( GameFolder/Shaders/)
	ShaderRawData(String filename, ShaderPathMode mode = ShaderPathMode::Name);

public:
	Shader GenerateShader()const;
};

