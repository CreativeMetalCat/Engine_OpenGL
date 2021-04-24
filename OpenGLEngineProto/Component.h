#pragma once
#include "Object.h"

//#include "Actor.h"


namespace Engine
{
	class CActor;

	class CComponent : public CObject
	{
		GENERATED_CLASS_BODY(Component,Object,Base,Engine)
	protected:
		
	public:
		CActor* Owner;

		CComponent(String name, CActor* owner);
	};
}

