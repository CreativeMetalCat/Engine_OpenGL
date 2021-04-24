#pragma once
#include "World.h"

namespace Engine
{
	/*This is the class that represents the game.
	This class manages worlds, shaders, window creation etc.
	*/
	class CGame
	{
	protected:
		/*Worlds that are currently loaded*/
		Array<CWorld*>worlds = Array<CWorld*>();

		/*Array of currently loaded shaders. Used to simply access to shaders and avoid loading same shader twice*/
		Array<Shader> shaders = Array<Shader>();
	public:
		/*Get's shader with the same name
		* note: if shader is not present in this world -> shader will be loaded
		* note2: value is returned as pointer to simplify giving information about shader not existing
		*/
		Shader* GetShader(String name)const;

	};
}

