#pragma once
#pragma once
#include "Character.h"


class Boss : public Character
{
	EYE_STATE m_eyeState;
	Circle m_sightRange;
	Timer*  m_timer;
	list<Object*> m_BossCircle;

public:
	Boss(int id) : Character(id)
	{
		m_state = CHARACTER_IDLE;
		m_eyeState = EYE_BLUE;
		m_timer = new Timer();
		RENDER->LoadImageFiles(TEXT("Boss_Idle"), TEXT("Image/Monster/Boss/Idle/Boss_Idle_"), TEXT("png"), 13);
		RENDER->LoadImageFiles(TEXT("Boss_Attack"), TEXT("Image/Monster/Boss/Attack/Boss_Attack_"), TEXT("png"), 5);
		RENDER->LoadImageFiles(TEXT("Eye_Green"), TEXT("Image/Monster/Boss/BossGreenEyes/GreenEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Blue"), TEXT("Image/Monster/Boss/BossBlueEyes/BlueEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Red"), TEXT("Image/Monster/Boss/BossRedEyes/RedEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Yellow"), TEXT("Image/Monster/Boss/BossYellowEyes/YellowEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("BossCircle_Blue"), TEXT("Image/Monster/Boss/BossBlueEyes/BlueEye"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("BossCircle_Red"), TEXT("Image/Monster/Boss/BossRedEyes/RedEye"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("BossCircle_Yellow"), TEXT("Image/Monster/Boss/BossYellowEyes/YellowEye"), TEXT("png"), 1);
		m_dir = Vector::Down();
		m_maxLife = 10000;

		/*for (int i = 0; i < 4; i++)
		{
			NEW_OBJECT(Object* m_pBossCircle, Boss(id));
			Vector circlePos = {};
			switch (i)
			{
			case 0: circlePos = Vector(700, 450);
			case 1: circlePos = Vector(570, 570);
			case 2: circlePos = Vector(1050, 450);
			case 3: circlePos = Vector(1150, 570);
			}


			m_pBossCircle->SetPosition(circlePos);

			m_BossCircle.push_back(m_pBossCircle);
		}*/


	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		}
		Animation()->Update(deltaTime);
		Animation()->Get(m_eyeState)->Update(deltaTime);
		m_timer->Update(deltaTime);
	}

	void IdleState()
	{
		Animation()->Play(BOSS_IDLE);



	}

	void AttackState()
	{




	}



	void Draw(Camera* pCamera)
	{		
		pCamera->Draw(Animation()->Get(m_eyeState)->GetSprite(), Position() + Vector(0, -22));
		pCamera->Draw(Animation()->Current()->GetSprite(), Position() + Vector(0, -100));
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
	}


};