#pragma once
#include "Character.h"


class Monster : public Character
{
	Circle m_sightRange;
	MONSTER_KIND m_kind;
	Vector m_standPos;
	Vector m_standDir;
	Timer*  m_timer;

public:
	Monster(int id) : Character(id)
	{
		m_sightRange.radius = 300;
		m_speed = 100;
		m_dirState = DIR_DOWN;
		m_timer = new Timer();
	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		case CHARACTER_CAST_END: CastingState(deltaTime); break;
		}
		Get_Dir_state();
		Animation()->Update(deltaTime);
		m_timer->Update(deltaTime);
		
	}

	void IdleState()
	{
		switch (m_dirState)
		{
		case DIR_UP: m_spriteState = MINION_IDLE_UP + m_kind; break;
		case DIR_LEFT: m_spriteState = MINION_IDLE_LEFT + m_kind; break;
		case DIR_RIGHT: m_spriteState = MINION_IDLE_RIGHT + m_kind; break;
		case DIR_DOWN: m_spriteState = MINION_IDLE_DOWN + m_kind; break;
		}
		Animation()->Play(m_spriteState);
		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), m_sightRange))
		{
			m_sightRange.radius = 300;
			m_state = CHARACTER_RUN;
		}
	}

	void RunState(float deltaTime)
	{

		switch (m_dirState)
		{
		case DIR_UP: m_spriteState = MINION_RUN_UP + m_kind; break;
		case DIR_LEFT: m_spriteState = MINION_RUN_LEFT + m_kind; break;
		case DIR_RIGHT: m_spriteState = MINION_RUN_RIGHT + m_kind; break;
		case DIR_DOWN: m_spriteState = MINION_RUN_DOWN + m_kind; break;
		}


		Animation()->Play(m_spriteState);

		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), m_sightRange))
		{

			if (SOUND->FindChannel("IntroBgm") != NULL)SOUND->Pause("IntroBgm");
			if (SOUND->FindChannel("Boss1Bgm") == NULL) { SOUND->Play("Boss1Bgm", 1.0f); }


			FowardToTargetPos(OBJECT->GetPlayer()->Position(), deltaTime);

			if (MATH->Distance(OBJECT->GetPlayer()->Position(), m_pos) <= 300.0f)
			{
				//m_state = CHARACTER_CAST_END;

				
				if (MATH->Distance(OBJECT->GetPlayer()->Position(), m_pos) <= 300.0f&&m_timer->CheckTime(2))
				{
					OBJECT->CreateSkill(this, USER_MINION, FIRE_BOLT);
				}
			}

		}
		else
		{

			FowardToTargetPos(m_standPos, deltaTime);

			if (MATH->SqrDistance(m_standPos, m_pos) <= 10.0f)
			{
				m_dir = m_standDir;
				m_sightRange.radius = 300;
				m_state = CHARACTER_IDLE;
			}

					if (SOUND->FindChannel("IntroBgm") != NULL)SOUND->Resume("IntroBgm");
					if (SOUND->FindChannel("Boss1Bgm") != NULL)SOUND->Stop("Boss1Bgm");

		}
	}


	void CastingState(float deltaTime)
	{
		//Animation()->Play(m_spriteState);

		if (MATH->Distance(OBJECT->GetPlayer()->Position(), m_pos) <= 300.0f)
		{
			OBJECT->CreateSkill(this, USER_MINION, FIRE_BOLT);
		}

	}

	void Draw(Camera* pCamera)
	{
		if (IsHideToWall())Animation()->Current()->GetSprite()->SetOpacity(0.5f);
		//pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		//pCamera->DrawCircle(m_sightRange.center, m_sightRange.radius, ColorF::Red, 2.0f);
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
		pCamera->Draw(Animation()->Current()->GetSprite(), Position());
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
		m_sightRange.center = m_pos;
	}

	void SetStandPosition()
	{
		m_standPos = m_pos;
		m_standDir = m_dir;
	}

	void SetMonsterKind(MONSTER_KIND kind)
	{
		m_kind = kind;
	}


};