#include "Material.h"
#include "stb_image.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "AssetLoader.h"

#include "Macros.h"

//a checkerboard pattern image exported from GIMP
static const char* fallback =
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
"";



uint Engine::Material::Material::get_gl_texture_const(int id)
{
	return (id >= 0 && id < 0x20) ? id : 0;
}

void Engine::Material::Material::load_null()
{
	//we have nothing to load from, but for the sake of making it easier to tell if something is broken we will display "null" texture
	std::pair<String, uint>texture;
	texture.first = "null";

	glGenTextures(1, &texture.second);
	glBindTexture(GL_TEXTURE_2D, texture.second);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const Image>(const_cast<char*>(fallback)));

	/*Currently all of the textures are loaded with GL_NEAREST, which gives textures that nice pixelated look*/
	//in the future(when different asset system will be finally implemented this will be loaded from that very file
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	textureData.push_back(texture);
}

uint Engine::Material::Material::GetTexture(String)
{
	return uint();
}

void Engine::Material::Material::Apply(uint ShaderProgramID)
{
	if (!textureData.empty())
	{
		for (int i = 0; i < textureData.size(); i++)
		{
			// Bind our texture in Texture Unit i
			glActiveTexture(GL_TEXTURE0 + get_gl_texture_const(i));
			glBindTexture(GL_TEXTURE_2D, textureData[i].second);
			// Set our sampler to use Texture Unit i
			glUniform1i(glGetUniformLocation(ShaderProgramID, textureData[i].first.c_str()), i);
		}

		//LOG_ERROR(glewGetErrorString(glGetError()), Engine::Material::Material::Apply, Name.c_str());
	}
}

Engine::Material::Material::Material()
{
	load_null();
}

Engine::Material::Material::Material(Map<String, String> textures)
{
	if (!textures.empty())
	{
		Image nullImage = reinterpret_cast<const Image>(const_cast<char*>(fallback));

		int height;//image height
		int width;//image width
		int comp;//channels

		
		for (int i = 0; i < textures.size(); i++)
		{
			bool useFallBack = false;
			std::pair<String, uint>texture;
			texture.first = textures[i].first;

			unsigned char* image = stbi_load(textures[i].second.c_str(), &height, &width, &comp, STBI_rgb_alpha);
			if (image == nullptr)
			{
				height = 16;
				width = 16;
				useFallBack = true;
				printf("Failed to load a texture. %s", textures[i].second.c_str());
			}

			glGenTextures(1, &texture.second);
			glBindTexture(GL_TEXTURE_2D, texture.second);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, useFallBack ? nullImage : image);

			/*Currently all of the textures are loaded with GL_NEAREST, which gives textures that nice pixelated look*/
			//in the future(when different asset system will be finally implemented this will be loaded from that very file
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glGenerateMipmap(GL_TEXTURE_2D);

			//remove the image -> we don't need it anymore
			delete[] image;

			textureData.push_back(texture);
		}
	}
}

Engine::Material::Material::Material(String assetFilePath)
{
	//here we will load .asset file and load every texture we need
	//this function's implementation relies on nlohmann's json library but only inside this function
	using json = nlohmann::json;
	json data = Helpers::LoadAssetFile(assetFilePath);
	if (data["asset_info"]["type"] == "material")
	{
		Image nullImage = reinterpret_cast<const Image>(const_cast<char*>(fallback));

		int height;//image height
		int width;//image width
		int comp;//channels

		int filter = data["pixelated_filter"].get<bool>() ? GL_NEAREST : GL_LINEAR;

		Name = data["name"].get<std::string>();

		for (auto it = data["textures"].begin(); it != data["textures"].end(); ++it)
		{
			if (!it.value().is_string()) { continue; }

			bool useFallBack = false;
			std::pair<String, uint>texture;
			texture.first = it.key();

			//All textures are stored in "Textures" folder
			unsigned char* image = stbi_load(("Textures/" + it.value().get<std::string>()).c_str(), &height, &width, &comp, STBI_rgb_alpha);
			if (image == nullptr)
			{
				height = 32;
				width = 32;
				useFallBack = true;
				printf("Error! Failed to load texture Name: %s\n", it.value().get<std::string>().c_str());
			}

			glGenTextures(1, &texture.second);
			glBindTexture(GL_TEXTURE_2D, texture.second);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, useFallBack ? nullImage : image);

			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

			glGenerateMipmap(GL_TEXTURE_2D);

			//remove the image -> we don't need it anymore
			delete[] image;

			textureData.push_back(texture);

			LOG_ERROR(glewGetErrorString(glGetError()), glGetError(), Engine::Material::Material::Material(String assetFilePath), Name.c_str());
		}
	}
	else
	{
		load_null();
	}
}

Engine::Material::Material::~Material()
{
	if (!textureData.empty())
	{
		for (int i = 0; i < (textureData.size()); i++)
		{
			glDeleteTextures(1, &textureData[i].second);
		}
	}
	textureData.~vector();
}
