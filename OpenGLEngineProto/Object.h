#pragma once
//tell engine to use default(more or less) c++ types
//for example -> std::string for string and glm::vec3 as vector
#define USE_DEFAULT_CPP

#include "Types.h"

#ifndef GENERATED_CLASS_BODY
#define GENERATED_CLASS_BODY(name,parentName,Namespace)\
void set_class_data_generated(){classInfo.Name = #name;classInfo.Parent = #parentName;}\
typedef Namespace::##C##parentName Super;
#endif // !GENERATED_CLASS_BODY



namespace Engine
{
	/*
	* This class stores info about the class it belongs to.
	* Implementation of *how* it defines which class it is is not good, as it uses simple string, but it's still better then doing dynamic_cast each time
	* THIS CLASS MUST BE PROPERLY SET IN EACH CHILD TO AVOID ISSUES
	*/
	struct ClassInfo
	{
	public:
		String Name = "Object";

		String Parent = "None";
	};

	class CObject
	{
	protected:
		bool isPendingDestroy = false;

		//MUST BE PROPERLY SET IN EACH CLASS TO AVOID ISSUES
		ClassInfo classInfo;
	public:

		ClassInfo GetClass()const { return classInfo; }

		bool Valid()const { return !isPendingDestroy; }

		String Name;

		virtual void Update(float deltaTime) {}

		/*
		* This function will be called when the game "starts" and is used for "in-world" object initialisations
		*/
		virtual void Init() = 0;

		CObject(String name) :Name(name) {}

		virtual void Destroy();
	};
}

