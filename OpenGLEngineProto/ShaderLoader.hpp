#pragma once

#include "Types.h"
namespace Helpers
{
	uint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	uint LoadShaders(String vertText, String fragText);

	std::pair<String, String> LoadShaderText(String filepath, ShaderPathMode mode);
}