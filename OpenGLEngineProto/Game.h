#pragma once
#include "Shader.h"
#include "Material.h"
#include "World.h"
#include "ControlTypes.h"
#include "Key.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Engine
{
	namespace Components::Camera
	{
		class CCameraComponent;
	}

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
		Array<ShaderRawData> shaders = Array<ShaderRawData>();

		/*Array of currently loaded materials. Used simplify access to materils and to avoid loading same textures for same materials more then once*/
		Array<Material::Material> materials = Array<Material::Material>();

		/*Render data from current camera*/
		RenderData currentRenderData;

		/*Current camera(the one that is used to get render data*/
		Engine::Components::Camera::CCameraComponent* currentCamera;
 	public:
		Key::KeyState GetKeyState(int key);

		/*Sets new current camera, that will be used for world
		* Currently always returns true(unless camera is not valid), as there are no way to fail
		*/
		bool SetCurrentCamera(Engine::Components::Camera::CCameraComponent*);

		/*Get render data for this scene*/
		RenderData GetCurrentRenderData()const;

		/*Get's shader with the same name
		* note: if shader is not present in this world -> shader will be loaded
		* note2: value is returned as pointer to simplify giving information about shader not existing
		*/
		Shader* GetShader(String name);

		/*Gets current position of the mouse on the screen*/
		Vector2 GetMousePosition()const;

		void SetMousePosition(Vector2);

		Vector2 GetWindowSize()const;

		/*Adds world to current world pool
		* IF world is already in the pool returns false
		*/
		bool AddWorld(CWorld* world);

		/* Returns material that has this name
		* note: if no material with this name is currently loaded -> it will be loaded
		*/
		Material::Material* GetMaterial(String name);

		/*Creates window and does basic setup*/
		bool CreateWindow(std::string name, int height = 1028,int width = 768);

		/*This is where the game will be happening, once this function exists execution -> that means that the game needs to be closed*/
		void Run();

		void SetMouseMode(MouseMode mode);

		~CGame();
	};
}

