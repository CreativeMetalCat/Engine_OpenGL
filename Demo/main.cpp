#define USE_DEFAULT_CPP

#pragma comment(lib,"Engine.lib")

#include "Game.h"
#include "StaticMeshComponent.h"
#include "CameraComponent.h"
#include "ModelLoader.h"

/*Generates a small world with some props*/
Engine::CWorld* create_debug_world(Engine::CGame* game)
{
	using namespace Engine;

	using CCameraComponent = Components::Camera::CCameraComponent;

	Engine::CWorld* world = new Engine::CWorld();
	world->game = game;


	CActor* chair = world->SpawnActor<CActor>(std::string("chair"), nullptr, Vector(1), Vector(0));
	chair->AddComponent<Components::CStaticMeshComponent>("static",new Material::Material({}), ModelLoader::LoadModel("models/SM_Chair.FBX", 0.01f), "color");

	CActor* floor = world->SpawnActor<CActor>(std::string("floor"),nullptr, Vector(0), Vector(0));
	floor->AddComponent<Components::CStaticMeshComponent>("static",new Material::Material({}), ModelLoader::LoadModel("models/basic/Floor_400x400.FBX", 0.01f), "color");
	
	CActor* player = world->SpawnActor<CActor>(String("Player"), nullptr, Vector(0), Vector(0));
	player->AddComponent<CCameraComponent>("camera", 60.f);

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