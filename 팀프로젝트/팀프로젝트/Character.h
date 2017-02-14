#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

class Character : public Object
{
protected:
	CHARACTER_STATE m_state;
	SPRITE_STATE m_spriteState;
	
	float m_speed;
	Circle m_circle;
	float m_life;
	DIR_STATE    m_dirState;
	float m_maxLife;

public:
	Character(int id) : Object(id)
	{
		m_state = CHARACTER_IDLE;
		m_dir = (Vector::Down()+Vector::Right()).Normalize();
		m_speed = 300;
		m_life = 1000;
		m_maxLife = m_life;

	}

	float MaxLife()
	{
		return m_maxLife;
	}

	float GetLife()
	{
		return m_life;
	}

	void SetLife(float damage)
	{
		m_life -= damage;
	}

	void SetCharacterCollider(float radius) 
	{ 
		m_circle.center = this->Position();
		m_circle.radius = radius;
	}
	Circle getCircle() { return m_circle; }
	virtual void SetPosition(Vector pos) 
	{ 
		this->m_pos = pos;
		m_circle.center = pos;
		
	}

	Vector GetDIr()
	{
		return m_dir;
	}

	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera) {  }
	virtual void Hit(float damage) { }
	virtual void SetMonsterKind(MONSTER_KIND kind) {}
	virtual void LoadingMonsterImage() {}

	bool IsGroundCollided()
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_GROUND);
		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				return true;
			}
		}
		return false;
	}

	bool IsHideToWall()
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_HIDE);
		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				return true;
			}
		}
		return false;
	}

	Vector GroundPush(Vector movedPos)
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_GROUND);

		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				movedPos -= MATH->GetOverlappedVector(this->getCircle(), (*it)->Collider());
			}
		}
		return movedPos;
	}

	void FowardToTargetPos(Vector targetPos, float deltaTime)
	{
		Vector prevPos = this->Position();
		Vector movedPos = this->Position();

		m_dir = Vector::Zero();

		m_dir = (targetPos - movedPos).Normalize();
		movedPos += m_dir * m_speed * deltaTime;
		if (IsGroundCollided())movedPos = GroundPush(movedPos);
		this->SetPosition(movedPos);
	}
	void Get_Dir_state()
	{
		DIR_STATE state = DIR_DOWN;

		float angle = MATH->ToAngle(m_dir);
		//cout << angle << endl;

		if (45.0f <= angle && angle <= 135.0f)m_dirState = DIR_UP;
		if (45.0f + 90.0f <= angle && angle <= 135.0f + 90.0f)m_dirState = DIR_LEFT;
		if (135.0f + 90.0f <= angle && angle <= 135.0f + 180.0f)m_dirState = DIR_DOWN;
		if (135.0f + 180.0f <= angle && angle <= 360.0f)m_dirState = DIR_RIGHT;
		if (45.0f >= angle)m_dirState = DIR_RIGHT;
		//cout << state << endl;
	}

};