#include "Shader.h"
#include "ShaderLoader.hpp"

ShaderRawData::ShaderRawData(String vertexShaderText, String fragmentShaderText)
	:VertexShaderText(vertexShaderText),FragmentShaderText(fragmentShaderText)
{
	if (vertexShaderText != "" && fragmentShaderText != "")
	{
		Valid = true;
	}
}

ShaderRawData::ShaderRawData(String filename,ShaderPathMode mode)
{
	auto text = Helpers::LoadShaderText("Shaders/"+filename, mode);
	if (text != std::pair<String, String>())
	{
		Valid = true;
		VertexShaderText = text.first;
		FragmentShaderText = text.second;
	}
}

Shader ShaderRawData::GenerateShader() const
{
	return { Helpers::LoadShaders(VertexShaderText, FragmentShaderText),Name };
}

ShaderRawData::~ShaderRawData()
{
	VertexShaderText.~basic_string();
	FragmentShaderText.~basic_string();
}
