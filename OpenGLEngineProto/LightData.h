#pragma once
/*LightData.h - file with structs that describe basic light data, like color, intensity, position*/
#define USE_DEFAULT_CPP
#include "Types.h"

/*
* Used to define what kind of light this is -> used to simplify loading data into shaders
*/
enum class LightType : char
{
	//VERY simple light that basically adds color to the world
	Ambient,
	//light that shines in every direction
	Point,
	//light that only shines in one narrow area
	Stoplight,
	//Similar to spotlight but has no world posistion
	Sun
};

/*
* base class for all light data
*/
struct LightData
{
	Color color;

	float Intensity = 0.f;

	/*Used to simply calculations and to keep using static light count-> if light is fake no calculaions will be done*/
	bool Fake = true;

	LightType Type = LightType::Ambient;
};


struct PointLightData :public LightData
{
	Vector Location;

	float Attenuetion;

	PointLightData() { Type = LightType::Point; }
};