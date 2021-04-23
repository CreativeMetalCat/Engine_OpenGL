#include "Component.h"

Engine::CComponent::CComponent(String name, CActor* owner)
	:CObject(name),Owner(owner)
{
	if (owner)
	{
		//do stuff
	}
	else
	{
		/*is this even a good idea?*/
		delete this;
	}
}
