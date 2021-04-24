#pragma once
#include "Shader.h"
#include "Material.h"
#include "World.h"
#include "ControlTypes.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/*This is the class that represents the game.
	This class manages worlds, shaders, window creation etc.
	*Functions must be called in this order
	* CreateWindow
	*/
	class CGame
	{
	protected:
		GLFWwindow* window;

		/*Worlds that are currently loaded*/
		Array<CWorld*>worlds = Array<CWorld*>();

		/*Array of currently loaded shaders. Used to simply access to shaders and avoid loading same shader twice*/
		Array<Shader> shaders = Array<Shader>();

		/*Array of currently loaded materials. Used simplify access to materils and to avoid loading same textures for same materials more then once*/
		Array<Material::Material> materials = Array<Material::Material>();
 	public:
		/*Get's shader with the same name
		* note: if shader is not present in this world -> shader will be loaded
		* note2: value is returned as pointer to simplify giving information about shader not existing
		*/
		Shader* GetShader(String name)const;

		/* Returns material that has this name
		* note: if no material with this name is currently loaded -> it will be loaded
		*/
		Material::Material* GetMaterial(String name)const;

		/*Creates window and does basic setup*/
		bool CreateWindow(std::string name, int height = 1028,int width = 768);

		/*This is where the game will be happening, once this function exists execution -> that means that the game needs to be closed*/
		void Run();

		void SetMouseMode(MouseMode mode);
	};
}

