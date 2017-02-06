#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"

enum SKILL_ATTRIBUTE
{
	ATTRIBUTE_FIRE, ATTRIBUTE_WATER, ATTRIBUTE_ELECTRICITY,

};

class Skill : public Object
{
	SKILL_ATTRIBUTE m_attribute;
	Vector          m_dir;
	float           m_damage;
	float           m_speed;

public:
	Skill(int id, Vector dir) : Object(id)
	{
	}

	void Update(float deltaTime)
	{
		
	}

	void Draw(Camera* pCamera)
	{
		
	}

	void Collied()
	{
		
	}
};