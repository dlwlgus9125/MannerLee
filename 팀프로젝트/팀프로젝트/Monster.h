#pragma once
#include "Character.h"

class Monster : public Character
{
	Circle sightRange;
	MONSTER_KIND kind;
	Vector m_standPos;
	Vector m_standDir;

public:
	Monster(int id) : Character(id)
	{
		sightRange.radius = 100;
		m_speed = 200;

	}

	void Update(float deltaTime)
	{
		
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		}
	}

	void IdleState()
	{
		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), sightRange))
		{
			sightRange.radius = 200;
			m_state = CHARACTER_RUN;
		}
	}

	void RunState(float deltaTime)
	{
		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), sightRange))
		{
			FowardToTargetPos(OBJECT->GetPlayer()->Position(), deltaTime);
		}
		else
		{
			FowardToTargetPos(m_standPos, deltaTime);

			if (MATH->SqrDistance(m_standPos, m_pos) <= 10.0f)
			{
				m_dir = m_standDir;
				sightRange.radius = 100;
				m_state = CHARACTER_IDLE;
			}
		}
	}

	void Draw(Camera* pCamera)
	{
		pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		pCamera->DrawCircle(sightRange.center, sightRange.radius, ColorF::Red, 2.0f);
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
		/*pCamera->Draw(Animation()->Current()->GetSprite(), Position(), -1);*/
	//	pCamera->DrawRect(Collider().LeftTop(), Collider().leftTop);
	}

	void Hit(float damage)
	{
		Animation()->Play(CHARACTER_HIT);
	}

	void SetPosition(Vector pos)
	{
		this->m_pos = pos;
		m_circle.center = pos;
		sightRange.center = m_pos;
	}

	void SetStandPosition()
	{
		m_standPos = m_pos;
		m_standDir = m_dir;
	}
	void BackStandPos()
	{

	}
};