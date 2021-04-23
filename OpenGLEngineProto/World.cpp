#include "World.h"

template<class Class, class ...Args>
inline Class* Engine::CWorld::SpawnActor(String name, CActor* owner, Args ...args)
{
	Class* actor = new Class(name, args);
	if (actor)
	{
		actors.push_back(actor);
		return actor;
	}
	return NULL;
}