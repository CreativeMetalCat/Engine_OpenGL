#include "Object.h"

void Engine::CObject::Destroy()
{
	isPendingDestroy = true;
}
