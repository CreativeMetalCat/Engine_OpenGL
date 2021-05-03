#define USE_DEFAULT_CPP

#pragma comment(lib,"Engine.lib")

#include "Game.h"
#include "StaticMeshComponent.h"
#include "CameraComponent.h"
#include "ModelLoader.h"

class Player :public Engine::CActor
{
	GENERATED_CLASS_BODY(Player,Actor,Player,Engine)
public:
	Player(String name, Engine::CWorld* world, CActor* owner = nullptr, Vector Location = Vector(0), Vector Rotation = Vector(0))
		:CActor(name,world,owner,Location,Rotation)
	{

	}

	float MovementSpeed = 0.1f;

	float MouseSpeed = 0.0005f;

	void Update(float deltaTime)override
	{

		Rotation.x += MouseSpeed * deltaTime * float(world->game->GetWindowSize().x / 2 - world->game->GetMousePosition().x);
		Rotation.y += MouseSpeed * deltaTime * float(world->game->GetWindowSize().y / 2 - world->game->GetMousePosition().y);

		world->game->SetMousePosition(Vector2(world->game->GetWindowSize().x / 2, world->game->GetWindowSize().y / 2));

		//printf("%f %f %f \n", Location.x, Location.y, Location.z);
		if (world->game->GetKeyState(GLFW_KEY_UP))
		{
			Location += GetForwardVector() * deltaTime * MovementSpeed;
		}
		if (world->game->GetKeyState(GLFW_KEY_DOWN))
		{
			Location -= GetForwardVector() * deltaTime * MovementSpeed;
		}
		if (world->game->GetKeyState(GLFW_KEY_RIGHT))
		{
			Location += GetRightVector() * deltaTime * MovementSpeed;
		}
		if (world->game->GetKeyState(GLFW_KEY_LEFT))
		{
			Location -= GetRightVector() * deltaTime * MovementSpeed;
		}
	}

};

/*Generates a small world with some props*/
Engine::CWorld* create_debug_world(Engine::CGame* game)
{
	using namespace Engine;

	using CCameraComponent = Components::Camera::CCameraComponent;

	Engine::CWorld* world = new Engine::CWorld();
	world->AmbientLightColor = Color(1, 1, 1);
	world->AmbientLightIntensity = 0.5;
	game->AddWorld(world);

	CActor* chair = world->SpawnActor<CActor>(std::string("chair"), nullptr, Vector(1), Vector(0));
	chair->AddComponent<Components::CStaticMeshComponent>("static","M_Test", ModelLoader::LoadModel("models/SM_Chair.FBX", 0.01f), "texture");

	CActor* floor = world->SpawnActor<CActor>(std::string("floor"),nullptr, Vector(0), Vector(0));
	floor->AddComponent<Components::CStaticMeshComponent>("static","M_Test", ModelLoader::LoadModel("models/basic/Floor_400x400.FBX", 0.01f), "texture");
	
	Player* player = world->SpawnActor<Player>(String("Player"), nullptr, Vector(0), Vector(0));
	player->AddComponent<CCameraComponent>("camera", 60.f);
	game->SetCurrentCamera(player->GetComponent<CCameraComponent>("camera"));

	return world;
}

int main()
{
	Engine::CGame* game = new Engine::CGame();
	game->CreateWindow("game");
	game->AddWorld(create_debug_world(game));
	game->Run();

	return 0;
}