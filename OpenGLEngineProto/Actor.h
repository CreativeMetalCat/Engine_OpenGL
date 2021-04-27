#pragma once
#include "Object.h"
#include "Component.h"

#include "World.h"


namespace Engine
{
	class CWorld;
	namespace Components
	{
		class CRenderComponent;
	}

	class CActor :public CObject
	{
		GENERATED_CLASS_BODY(Actor,Object,Base,Engine)
			
	protected:
		Array<CComponent*> components  = Array<CComponent*>();
		
		/*World in which actor exists*/
		CWorld* world;
	public:
		CActor* Owner = nullptr;

		CWorld* GetWorld()const { return world; }

		Array<CActor*>Children = Array<CActor*>();

		Vector Location;

		Vector Rotation;

		Vector Scale;

		Vector GetForwardVector() const;

		Vector GetRightVector() const;

		Vector GetWorldLocation()const;

		Vector GetWorldRotation()const;

		/*Returns component with the same name or null if such component was not found*/
		template<class Class> Class* GetComponent(String name);

		CActor(String name, CWorld* world, CActor* owner = nullptr, Vector Location = Vector(0), Vector Rotation = Vector(0));

		/*Creates new components and adds to actor's storage
		* NAME MUST BE UNIQUE
		*/
		template<class Class, class ... Args> Class* AddComponent(String name, Args ... args);

		// Inherited via CObject
		virtual void Init() override;

		virtual void Update(float deltaTime);

		/*Called when *any* render component is drawn.
		Use this function to set values in shaders*/
		virtual void OnComponentDraw(Components::CRenderComponent* comp);
	};
	
	template<class Class, class ...Args>
	inline Class* CActor::AddComponent(String name, Args ... args)
	{
		//do a check, because name must be unique
		if (std::find_if(components.begin(), components.end(), [name](CComponent* comp) {return comp->Name == name; }) == components.end())
		{
			//create class 
			Class* comp = new Class(name, this, args...);
			if (comp)
			{
				components.push_back(comp);
				return comp;
			}
		}
		return NULL;
	}


	template<class Class> inline Class* Engine::CActor::GetComponent(String name)
	{
		if (components.empty()) { return nullptr; }
		return static_cast<Class*>(*std::find_if(components.begin(), components.end(), [name](CComponent* comp) {return comp->Name == name; }));
	}

}

