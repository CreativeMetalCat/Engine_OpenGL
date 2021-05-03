#include "AssetLoader.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

json Helpers::LoadAssetFile(String filename)
{
	// Read the Fragment Shader code from the file
	std::string assetText;
	std::ifstream assetStream(filename, std::ios::in);
	if (assetStream.is_open())
	{
		std::stringstream sstr;
		sstr << assetStream.rdbuf();
		assetText = sstr.str();
		assetStream.close();
	}

	return json::parse(assetText);
}
