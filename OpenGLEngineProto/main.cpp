//main.cpp - fail where all of the magic starts -> responsible for creating everything needed to start an app

#include "RenderObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Shapes.hpp"
#include "CameraPlayer.hpp"


#ifndef TINYOBJLOADER_IMPLEMENTATION
#include "ModelLoader.h"
#else
#error TinyObjLoader was included more then once.
#endif // !TINYOBJLOADER_IMPLEMENTATION

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Light.h"


int main()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(1024, 768, "RenderPal", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3(and up) compatible.This engine uses 4.0\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 400 core");

	

	

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glm::mat4 projection = glm::perspective(glm::radians(45.f), 4.f/3.f, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt
	(
		glm::vec3(4,3,-3),//camera pos
		glm::vec3(0, 0, 0),//what to look at
		glm::vec3(0, 1, 0)//up vector
	);

	glm::mat4 model = glm::mat4(1.0f);
	

	
	
	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	
	
	std::vector<CRenderObject*>objects = std::vector<CRenderObject*>();

	auto models = ModelLoader::LoadModelFromScene("models/Scenes/scene_test.fbx", 0.01f);
	int i = 0;
	for (auto it = models.begin(); it != models.end(); ++it)
	{
		objects.push_back(new CRenderObject
		(
			(*it).Data,//load mesh data
			"Textures/" + (*it).MaterialNames[0],//what texure to use
			"texture"//what shader to use
		));
		objects[i]->Location = (*it).RelativeLocation;
		//objects[i]->Rotation = (*it).RelativeRotation;.
		objects[i]->Rotation.x -= 90;
		objects[i]->Scale = glm::vec3((*it).Scale);
		i++;
	}
	objects.push_back(new CRenderObject(ModelLoader::LoadModel("models/SM_building_08.FBX",0.00001f).Data, "", "color"));
	objects[0]->Location.x -= 100;
	objects[0]->Location.y -= 50;
	objects[0]->Rotation.z += 90;


	std::vector<Light> pointLights = std::vector<Light>();
	//fill it with empty lights for now
	for (int i = 0; i < 6/*this variable here MUST match MAX_LIGHTS in shader*/; i++)
	{
		pointLights.push_back(Light(glm::vec3(0), 1, 0, glm::vec3((rand() % 100) / 10, (rand() % 100)/10, (rand() % 100) / 10)));
		pointLights[i].Fake = false;
	}
	pointLights[0].Fake = false;
	pointLights[0].Color = glm::vec3(1, 0, 0);

	CCameraPlayer* camera = new CCameraPlayer(window, glm::vec3(1),60.f,0.01f,0.0005f);
	glm::vec3 test_light_location = glm::vec3(0);
	float test_light_intensity = 1;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	
	do 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
		
		
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			pointLights[0].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			pointLights[1].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			pointLights[2].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			pointLights[3].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			pointLights[4].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			pointLights[5].Location = camera->Location;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
		{
			pointLights[0].Intensity -= 0.01;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
		{
			pointLights[0].Intensity += 0.01;
		}
		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		camera->Update(deltaTime);

		glm::mat4 mvp = model;

		if (!objects.empty())
		{
			for (auto it = objects.begin(); it != objects.end(); ++it)
			{
				if ((*it)->ShouldUpdate)
				{
					(*it)->Update(deltaTime);
				}
				(*it)->Draw({ camera->GetPerspective() , camera->GetViewMatrix(),pointLights });
			}
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("WorldEdit");
		ImGui::Text("fdfdfd");
		ImGui::Button("aaaa");
		ImGui::End();
		ImGui::Render();
		if (ImGui::GetDrawData())
		{
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteVertexArrays(1, &VertexArrayID);

	for (auto it = objects.end()-1; it != objects.begin(); it--)
	{
		delete (*it);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}