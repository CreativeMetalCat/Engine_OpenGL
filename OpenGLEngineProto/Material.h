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

		void load_null();
	protected:
		//Array of pairs with key being location that texture will be binded to and value being the texture itself
		Map<String, uint> textureData;
	public:
		Material(const Material&) = delete;

		Material& operator=(const Material&) = delete;
		
		String Name;

		
		uint GetTexture(String);

		//Map<String, Image> Textures;

		void Apply(uint ShaderProgramID);

		Material();

		/*Map<String, String>textures ->
		> first string is what kind of texture this is (diffuse,normal,etc.) <- this name is what name will be used when passing to shaders
		> Second string is texture path 
		*/
		[[deprecated]]
		Material(Map<String, String>textures);

		Material(String assetFilePath);

		~Material();
	};
}