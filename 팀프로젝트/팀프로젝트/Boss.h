#pragma once
#pragma once
#include "Character.h"
#include "SceneManager.h"

class Boss : public Character
{
	EYE_STATE m_eyeState;
	Circle m_sightRange;
	Timer*  m_timer;
	list<Object*> m_BossCircle;
	RotateDir*      m_rotateDir;
	float m_attackTime;
	bool isBossDie;
	int  exitTime;
	float exitchecker;

public:
	Boss(int id) : Character(id)
	{

		srand((unsigned)time(NULL));
		m_state = CHARACTER_IDLE;
		m_eyeState = EYE_GREEN;
		m_timer = new Timer();
		m_rotateDir = new RotateDir();
		isBossDie = false;
		exitTime = 0;
		exitchecker = 0.0f;
		m_maxLife = 2000.0f;
		m_life = m_maxLife;
		
		RENDER->LoadImageFiles(TEXT("Boss_Idle"), TEXT("Image/Monster/Boss/Idle/Boss_Idle_"), TEXT("png"), 13);
		RENDER->LoadImageFiles(TEXT("Boss_Attack"), TEXT("Image/Monster/Boss/Attack/Boss_Attack_"), TEXT("png"), 5);
		RENDER->LoadImageFiles(TEXT("Eye_Green"), TEXT("Image/Monster/Boss/BossGreenEyes/GreenEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Blue"), TEXT("Image/Monster/Boss/BossBlueEyes/BlueEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Red"), TEXT("Image/Monster/Boss/BossRedEyes/RedEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Eye_Yellow"), TEXT("Image/Monster/Boss/BossYellowEyes/YellowEye"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("BossCircle_Blue"), TEXT("Image/Monster/Boss/BlueCircle"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("BossCircle_Red"), TEXT("Image/Monster/Boss/RedCircle"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("BossCircle_Purple"), TEXT("Image/Monster/Boss/PurpleCircle"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Boss_Death"), TEXT("Image/Monster/Boss/BossDeath/Boss_Death_"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Eye_Death"), TEXT("Image/Monster/Boss/BossDeath/DeathEye"), TEXT("png"), 1);
	

		SOUND->LoadFile("BossAttack", "Sound/Effect/BossAttack.wav", false);
		SOUND->LoadFile("BossDie", "Sound/Effect/BossDeath.wav", false);

		m_attackTime = 0;
		m_dir = Vector::Down();

		for (int i = 0; i < 4; i++)
		{
			NEW_OBJECT(Object* m_pBossCircle, Monster(id));
			Vector circlePos = {};
			switch (i)
			{
			case 0: circlePos = Vector(690, 450); break;
			case 1: circlePos = Vector(570, 570); break;
			case 2: circlePos = Vector(1090, 450); break;
			case 3: circlePos = Vector(1190, 570); break;
			}


			m_pBossCircle->SetPosition(circlePos);

			m_BossCircle.push_back(m_pBossCircle);
		}


	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_CAST_END: AttackState(deltaTime); break;
		case CHARACTER_DEATH: DeathState(deltaTime); break;
		}
		Animation()->Update(deltaTime);
		Animation()->Get(m_eyeState)->Update(deltaTime);
		m_timer->Update(deltaTime);
		m_rotateDir->Update(deltaTime);
		
	}

	void IdleState()
	{
		Animation()->Play(BOSS_IDLE);

		if (m_timer->CheckTime(5)&& OBJECT->GetPlayer()->isComeBossMap()==true&&SOUND->FindChannel("BossVoice") == NULL)
		{
			int check = rand() % 3;
			switch (check)
			{
			case 0:m_eyeState = EYE_RED; break;
			case 1:m_eyeState = EYE_BLUE; break;
			case 2:m_eyeState = EYE_YELLOW; break;
			}
			SOUND->Play("BossAttack", 2.0f);
			m_state = CHARACTER_CAST_END;

		}
		if (m_life <= 0.0f)
		{
			m_state = CHARACTER_DEATH;
		}
	}

	void AttackState(float deltaTime)
	{
		Animation()->Play(BOSS_ATTACK);
		if (m_timer->CheckTime(1))
		{
			FOR_LIST(Object*, m_BossCircle)
			{
				(*it)->SetDir((OBJECT->GetPlayer()->Position()- (*it)->Position()).Normalize());
			switch (m_eyeState)
			{
			case EYE_RED:OBJECT->CreateSkill((*it), USER_MINION, FIRE_BOLT); SOUND->Play("FireBoltShot", 2.0f); break;
			case EYE_BLUE:OBJECT->CreateSkill((*it), USER_MINION, WATER_BOLT); SOUND->Play("WaterBoltShot", 2.0f); break;
			case EYE_YELLOW:OBJECT->CreateSkill((*it), USER_MINION, ELECTRICITY_BOLT); SOUND->Play("ElectBoltShot", 2.0f); break;
			}

			
			
				
			}

		}
		m_attackTime += deltaTime;

		if (m_attackTime >= 10)
		{
			m_attackTime = 0;
			
			m_state = CHARACTER_IDLE;
		}
		if (m_life <= 0.0f)
		{
			m_state = CHARACTER_DEATH;
		}
	}

	void DeathState(float deltaTime)
	{
		Animation()->Play(BOSS_DEATH);
		OBJECT->GetPlayer()->setFadeOut(true);
		m_eyeState = EYE_DEATH;
		if (isBossDie == false)SOUND->Play("BossDie", 2.0f);
		if (isBossDie == false)
		{
			isBossDie = true;
		}

		exitchecker += deltaTime;
		if (exitchecker >= 10.0f)
		{
			exitTime++;
		}
		if (exitTime >= 10)
		{
			SCENE->ChangeScene(SCENE_TITLE);

		}


	}



	void Draw(Camera* pCamera)
	{		
		pCamera->Draw(Animation()->Get(m_eyeState)->GetSprite(), Position() + Vector(0, -22));
		pCamera->Draw(Animation()->Current()->GetSprite(), Position() + Vector(0, -100));
		

		FOR_LIST(Object*, m_BossCircle)
		{
			if(m_eyeState!=EYE_GREEN&&m_eyeState!=EYE_DEATH)pCamera->Draw(Animation()->Get(m_eyeState + 100)->GetSprite(), (*it)->Position(), m_rotateDir->GetRotateDir());
		}
		
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
	}

	EYE_STATE GetEyeState() { return m_eyeState; }
	
};