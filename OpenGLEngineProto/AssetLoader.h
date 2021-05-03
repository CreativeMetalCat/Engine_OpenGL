//because assets are stored as json files
#include "json/json.hpp"
#include "Types.h"

namespace Helpers
{
	//loads asset by name and creates a json based on it
	nlohmann::json LoadAssetFile(String filename);
}