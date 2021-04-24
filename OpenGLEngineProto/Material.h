#pragma once

#include "Types.h"

namespace Engine::Material
{
	/*Class that is used to hold various texture data
	* Once data is loaded image data is deleted and only OpenGL data is kept and used
	*/
	class Material
	{
	private:
		uint get_gl_texture_const(int id);
	protected:
		//Array of pairs with key being location that texture will be binded to and value being the texture itself
		Map<String, uint> textureData;
	public:

		uint GetTexture(String);

		//Map<String, Image> Textures;

		void Apply(uint ShaderProgramID);

		/*Map<String, String>texures ->
		> first string is what kind of texure this is (diffuse,normal,etc.) <- this name is what name will be used when passing to shaders
		> Second string is texture path 
		*/
		Material(Map<String, String>textures);

		~Material();
	};
}