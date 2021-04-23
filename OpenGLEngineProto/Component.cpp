#include "Component.h"

Engine::CComponent::CComponent(String name, CActor* owner)
	:CObject(name),Owner(owner)
{
	if (owner)
	{
		set_class_data_generated();
	}
	else
	{
		/*is this even a good idea?*/
		delete this;
	}
}
