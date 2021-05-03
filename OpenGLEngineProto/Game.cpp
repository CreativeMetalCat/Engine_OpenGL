#include "Game.h"

#include "ShaderLoader.hpp"
#include <algorithm>
#include "CameraComponent.h"

Engine::Key::KeyState Engine::CGame::GetKeyState(int key)
{
	return (Key::KeyState)glfwGetKey(window,key);
}

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

Shader* Engine::CGame::GetShader(String name) 
{
    if (!shaders.empty())
    {
        Array<ShaderRawData>::const_iterator result = std::find_if(shaders.begin(), shaders.end(), [name](ShaderRawData shader) {return shader.Name == name; });
        if (result != shaders.end())
        {
			return new Shader((*result).GenerateShader());
        }
    }

    //"Shaders/"
	ShaderRawData data = ShaderRawData(name);
	if (data.Valid)
	{
		shaders.push_back(data);
		return new Shader((data.GenerateShader()));
	}
    return nullptr;
}

Vector2 Engine::CGame::GetMousePosition() const
{	
	//Mouse coords relative to the screen
	GLdouble xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return Vector2(xPos, yPos);
}

void Engine::CGame::SetMousePosition(Vector2 pos)
{
	glfwSetCursorPos(window, pos.x, pos.y);
}

Vector2 Engine::CGame::GetWindowSize() const
{
	GLint width, height;
	glfwGetWindowSize(window, &width, &height);

	return Vector2(width, height);
}

Engine::Material::Material* Engine::CGame::GetMaterial(String name)
{
	if (!materials.empty())
	{
		Array<Material::Material>::const_iterator iter = std::find_if(materials.begin(), materials.end(), [name](Material::Material mat) {return mat.Name == name; });
		if (iter != materials.end())
		{
			return new Material::Material(*iter);
		}
	}

	//we don't have this asset loaded yet -> try to load it and it doesn't matter if loading found the result, because material has fallback methods
	Material::Material* mat = new Material::Material("Materials/"+name);
	materials.push_back(*mat);

	return mat;
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
	glfwSetInputMode(window, GLFW_CURSOR, MouseMode::Hidden);
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

			Color totalAmbientLight = Color(0);

			for (int i = 0; i < worlds.size(); i++)
			{
				worlds[i]->Update(deltaTime);
				//calculate current ambient light by adding light from all worlds
				totalAmbientLight += worlds[i]->AmbientLightColor * worlds[i]->AmbientLightIntensity * (float)worlds[i]->AmbientLightEnabled;
			}
			//we update after worlds to account for updates of location, rotation, etc.
			if (currentCamera)
			{
				currentRenderData.CameraPerspective = currentCamera->GetPerspective();
				currentRenderData.CameraView = currentCamera->GetViewMatrix();
			}
			currentRenderData.AmbientLightColor = totalAmbientLight;
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