#pragma once
#include "Character.h"

class Monster : public Character
{
	Circle m_sightRange;
	MONSTER_KIND m_kind;
	Vector m_standPos;
	Vector m_standDir;

public:
	Monster(int id) : Character(id)
	{
		m_sightRange.radius = 100;
		m_speed = 100;
		m_dirState = DIR_DOWN;
	}

	void Update(float deltaTime)
	{
		LoadingMonsterImage();
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		}
		Get_Dir_state();
		Animation()->Update(deltaTime);
	}

	void IdleState()
	{
		switch (m_dirState)
		{
		case DIR_UP: m_spriteState = MINION_IDLE_UP; break;
		case DIR_LEFT: m_spriteState = MINION_IDLE_LEFT; break;
		case DIR_RIGHT: m_spriteState = MINION_IDLE_RIGHT; break;
		case DIR_DOWN: m_spriteState = MINION_IDLE_DOWN; break;
		}
		Animation()->Play(m_spriteState);
		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), m_sightRange))
		{
			m_sightRange.radius = 200;
			m_state = CHARACTER_RUN;
		}
	}

	void RunState(float deltaTime)
	{
		switch (m_dirState)
		{
		case DIR_UP: m_spriteState = MINION_RUN_UP; break;
		case DIR_LEFT: m_spriteState = MINION_RUN_LEFT; break;
		case DIR_RIGHT: m_spriteState = MINION_RUN_RIGHT; break;
		case DIR_DOWN: m_spriteState = MINION_RUN_DOWN; break;
		}


		Animation()->Play(m_spriteState);

		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), m_sightRange))
		{
			FowardToTargetPos(OBJECT->GetPlayer()->Position(), deltaTime);
		}
		else
		{
			FowardToTargetPos(m_standPos, deltaTime);

			if (MATH->SqrDistance(m_standPos, m_pos) <= 10.0f)
			{
				m_dir = m_standDir;
				m_sightRange.radius = 100;
				m_state = CHARACTER_IDLE;
			}
		}
	}

	void Draw(Camera* pCamera)
	{
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

	void LoadingMonsterImage()
	{
		/*TCHAR Address[200] = {};
		switch (m_kind)
		{
		case MONSTER_MINION_RED:
		{
			wsprintf(Address, TEXT("Image/Monster/%s/Idle/Up/Up"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Idle_Up"), TEXT("FireMinion"), TEXT("png"), 1);
			wsprintf(Address, TEXT("Image/Monster/%s/Idle/Down/Down"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Idle_Down"), Address, TEXT("png"), 1);
			wsprintf(Address, TEXT("Image/Monster/%s/Idle/Left/Left"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Idle_Left"), Address, TEXT("png"), 1);
			wsprintf(Address, TEXT("Image/Monster/%s/Idle/Right/Right"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Idle_Right"), Address, TEXT("png"), 1);

			wsprintf(Address, TEXT("Image/Monster/%s/Run/Up/Up"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Run_Up"), Address, TEXT("png"), 3);
			wsprintf(Address, TEXT("Image/Monster/%s/Run/Down/Down"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Run_Down"), Address, TEXT("png"), 3);
			wsprintf(Address, TEXT("Image/Monster/%s/Run/Left/Left"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Run_Left"), Address, TEXT("png"), 3);
			wsprintf(Address, TEXT("Image/Monster/%s/Idle/Right/Right"), TEXT("FireMinion"));
			RENDER->LoadImageFiles(TEXT("Minion_Run_Right"), Address, TEXT("png"), 3);

		}break;

		}*/
		
		

		


		RENDER->LoadImageFiles(TEXT("Minion_Idle_Up"), TEXT("Image/Monster/FireMinion/Idle/Up/Up"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Minion_Idle_Down"), TEXT("Image/Monster/FireMinion/Idle/Down/Down"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Minion_Idle_Left"), TEXT("Image/Monster/FireMinion/Idle/Left/Left"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Minion_Idle_Right"), TEXT("Image/Monster/FireMinion/Idle/Right/Right"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Minion_Run_Up"), TEXT("Image/Monster/FireMinion/Run/Up/Up"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Minion_Run_Down"), TEXT("Image/Monster/FireMinion/Run/Down/Down"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Minion_Run_Left"), TEXT("Image/Monster/FireMinion/Run/Left/Left"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Minion_Run_Right"), TEXT("Image/Monster/FireMinion/Run/Right/Right"), TEXT("png"), 3);


	}
};