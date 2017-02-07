#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

class Character : public Object
{
	CHARACTER_STATE m_state;
	Vector m_dir;
	float m_speed;
	Circle m_circle;

public:
	Character(int id) : Object(id)
	{
		m_state = CHARACTER_IDLE;
		m_dir = Vector::Down();
		m_speed = 300;

	}

	void SetCharacterCollider(float radius) 
	{ 
		m_circle.center = this->Position();
		m_circle.radius = radius;
	}
	Circle getCircle() { return m_circle; }
	void SetPosition(Vector pos) 
	{ 
		this->m_pos = pos;
		m_circle.center = pos;
		
	}

	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera) {  }
	virtual void Hit(float damage) { }

};