#include "AssetLoader.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Macros.h"

nlohmann::json Helpers::LoadAssetFile(String filename)
{
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
		LOG(("Failed to read asset file: " + filename).c_str(), Helpers::LoadAssetFile(String filename), );
		return nlohmann::json::parse("{\"asset_info\":{\"type\":\"none\"}}");
	}
	return nlohmann::json::parse(assetText);
}
