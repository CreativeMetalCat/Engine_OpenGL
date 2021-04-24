#include "Game.h"

#include "ShaderLoader.hpp"
#include <algorithm>

Shader* Engine::CGame::GetShader(String name) const
{
    if (!shaders.empty())
    {
        Array<Shader>::const_iterator result = std::find_if(shaders.begin(), shaders.end(), [name](Shader shader) {return shader.Name == name; });
        if (result != shaders.end())
        {
            return new Shader(*result);
        }
    }
    uint id = Helpers::LoadShaders(std::string("Shaders/" + name + "Vertex.glsl").c_str(), std::string("Shaders/" + name + "Fragment.glsl").c_str());
    if (id != 0)
    {
        return new Shader(id, name);
    }

    return nullptr;
}
