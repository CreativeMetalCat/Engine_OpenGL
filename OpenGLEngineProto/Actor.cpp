#include "Actor.h"

template<class Class, class ...Args>
inline Class* Engine::CActor::AddComponent(String name, Args ...args)
{
	Class* comp = new Class(name, args);
	if (comp)
	{
		components.push_back(comp);
		return comp;
	}
	return NULL;
}

Engine::CActor::CActor(String name, CActor* _owner):CObject(name), owner(_owner)
{
	classInfo.Name = "Actor";
	classInfo.Parent = "Object";
}

Engine::CActor::CActor(String name, Vector location, Vector rotation, CActor* _owner)
	: CObject(name), Location(location),Rotation(rotation), owner(_owner)
{
	classInfo.Name = "Actor";
	classInfo.Parent = "Object";
}
