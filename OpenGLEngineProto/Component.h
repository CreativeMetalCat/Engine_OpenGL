#pragma once
#include "Object.h"
class CActor;

namespace Engine
{
	class CComponent : public CObject
	{
	protected:
		
	public:
		CActor* Owner;

		CComponent(String name, CActor* owner);
	};
}

