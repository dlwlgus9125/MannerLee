#pragma once
#include "Character.h"

class Monster : public Character
{
	Circle sightRange;
	MONSTER_KIND kind;

public:
	Monster(int id) : Character(id)
	{
		sightRange.radius = 100;
		m_speed = 200;
		
	}

	void Update(float deltaTime)
	{
		
		if(MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), sightRange))
		{ 
			Vector prevPos = this->Position();
			Vector movedPos = this->Position();

			m_dir = Vector::Zero();
			Vector targetPos = OBJECT->GetPlayer()->Position();


			m_dir = (targetPos - movedPos).Normalize();


			
				movedPos += m_dir * m_speed * deltaTime;
				this->SetPosition(movedPos);
		
				if (!IsGroundCollided()) this->SetPosition(prevPos);
		}
		


	}

	void Draw(Camera* pCamera)
	{
		pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		pCamera->DrawCircle(sightRange.center, sightRange.radius, ColorF::Red,2.0f);
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
};