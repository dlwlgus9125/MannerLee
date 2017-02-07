#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"

class Monster : public Object
{
public:
	Monster(int id) : Object(id)
	{
	}

	void Update(float deltaTime)
	{
		Animation()->Update(deltaTime);
	}

	void Draw(Camera* pCamera)
	{
		pCamera->Draw(Animation()->Current()->GetSprite(), Position(), -1);
	//	pCamera->DrawRect(Collider().LeftTop(), Collider().leftTop);
	}

	void Hit(float damage)
	{
		Animation()->Play(CHARACTER_HIT);
	}
};