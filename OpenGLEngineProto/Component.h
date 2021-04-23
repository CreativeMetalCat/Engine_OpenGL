#pragma once
#include "Object.h"
class CActor;

namespace Engine
{
	class CComponent : public CObject
	{
		GENERATED_CLASS_BODY(Component,Object,Engine)
	protected:
		
	public:
		CActor* Owner;

		CComponent(String name, CActor* owner);
	};
}

