#include "Material.h"
#include "stb_image.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>


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
	return 0x84C0 + (id >= 0 && id < 32) ? id : 0;
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
			glActiveTexture(get_gl_texture_const(i));
			glBindTexture(GL_TEXTURE_2D, textureData[i].second);
			// Set our sampler to use Texture Unit i
			glUniform1i(glGetUniformLocation(ShaderProgramID,textureData[i].first.c_str()), i);
		}
	}
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
			std::pair<String, uint>texure;
			texure.first = textures[i].first;

			unsigned char* image = stbi_load(textures[i].second.c_str(), &height, &width, &comp, STBI_rgb_alpha);
			if (image == nullptr)
			{
				height = 16;
				width = 16;
				useFallBack = true;
				printf("Failed to load a texure. %s", textures[i].second.c_str());
			}

			glGenTextures(1, &texure.second);
			glBindTexture(GL_TEXTURE_2D, texure.second);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, useFallBack ? nullImage : image);

			/*Currently all of the textures are loaded with GL_NEAREST, which gives textures that nice pixelated look*/
			//in the future(when different asset system will be finally implemented this will be loaded from that very file
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glGenerateMipmap(GL_TEXTURE_2D);

			//remove the image -> we don't need it anymore
			delete[] image;

			textureData.push_back(texure);
		}
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
