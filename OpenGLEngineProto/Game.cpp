#include "Game.h"

#include "ShaderLoader.hpp"
#include <algorithm>
#include "CameraComponent.h"

bool  Engine::CGame::SetCurrentCamera(Engine::Components::Camera::CCameraComponent* camera)
{
	if (camera && camera->Valid())
	{
		currentCamera = camera;
		return true;
	}
	return false;
}

RenderData Engine::CGame::GetCurrentRenderData()const
{
	if (currentCamera)
	{
		return currentRenderData;
	}
	else
	{
		return RenderData();
	}
}

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

Engine::Material::Material* Engine::CGame::GetMaterial(String name) const
{
    return nullptr;
}

bool Engine::CGame::CreateWindow(std::string name, int height, int width)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.0, no reason here, just seemed like not that old but that young version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(height, width, name.c_str(), NULL, NULL);
	if (window == NULL) 
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3(and up) compatible.This engine uses 4.0\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	//that's the openGl version this engine uses
	ImGui_ImplOpenGL3_Init("#version 400 core");

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, MouseMode::Normal);
}

void Engine::CGame::Run()
{
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!worlds.empty())
		{
			
			// glfwGetTime is called only once, the first time this function is called
			static double lastTime = glfwGetTime();

			// Compute time difference between current and last frame
			double currentTime = glfwGetTime();
			float deltaTime = float(currentTime - lastTime);

			
			for (int i = 0; i < worlds.size(); i++)
			{
				worlds[i]->Update(deltaTime);
			}
			//we update after worlds to account for updates of location, rotation, etc.
			if (currentCamera)
			{
				currentRenderData = { currentCamera->GetPerspective(), currentCamera->GetViewMatrix(), {} };
			}
		}
		else
		{
			//no worlds -> no game
			//break;
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwWindowShouldClose(window) == 0);
}

bool Engine::CGame::AddWorld(Engine::CWorld* world)
{
	if (worlds.empty())
	{
		world->game = this;
		worlds.push_back(world);
		return true;
	}
	else
	{
		if (worlds.end() == std::find(worlds.begin(), worlds.end(), world))
		{
			world->game = this;
			worlds.push_back(world);
			return true;
		}
	}
	return false;
}

void Engine::CGame::SetMouseMode(MouseMode mode)
{
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

Engine::CGame::~CGame()
{
	const uint count = worlds.size();
	for (int i = count - 1; i > Index_None; --i)
	{
		delete worlds[i];
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}