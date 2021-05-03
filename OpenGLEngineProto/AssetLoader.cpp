#include "AssetLoader.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

nlohmann::json Helpers::LoadAssetFile(String filename)
{
	// Read the Fragment Shader code from the file
	std::string assetText;
	std::ifstream assetStream(filename + ".asset", std::ios::in);
	if (assetStream.is_open())
	{
		std::stringstream sstr;
		sstr << assetStream.rdbuf();
		assetText = sstr.str();
		assetStream.close();
	}

	if (assetText == "")
	{
		return nlohmann::json::parse("{asset_info:{\"type\":\"none\"}}");
	}
	return nlohmann::json::parse(assetText);
}
