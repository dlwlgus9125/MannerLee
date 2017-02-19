#pragma once
#include "Character.h"
#include "UIManager.h"

class Player : public Character
{
	Timer* m_timer;
	SKILL_ATTRIBUTE m_attribute;
	SKILL_ATTRIBUTE m_prevAttribute;
	SKILL_TYPE      m_skillType;
	SKILL_TYPE      m_prevSkillType;
	RotateDir*      m_rotateDir;
	Timer*          m_Timer;

	RUNE_STATE      m_Rune;
	RUNE_STATE      m_RuneType;

	CORRECT_STATE   m_correct;

	Vector          m_targetPos;
	int             m_circleGage;
	float             m_checkGage;
public:
	Player(int id) : Character(id)
	{
		m_state = CHARACTER_IDLE;
		m_dir = Vector::Down();
		m_dirState = DIR_DOWN;
		m_speed = 150;
		m_timer = new Timer();
		m_attribute = ATTRIBUTE_NONE;
		m_prevAttribute = ATTRIBUTE_NONE;
		m_skillType = TYPE_NONE;
		m_prevSkillType = TYPE_NONE;
		m_rotateDir = new RotateDir();
		m_timer = new Timer();
		m_life = 500;
		m_targetPos = m_pos;
		m_circleGage = 1;
		m_checkGage = 1.0f;
		m_Rune = RUNE_NONE;
		m_RuneType = RUNE_NONE;
		m_correct = CORRECT_NONE;

		OBJECT->LoadingMonsterImage();

		RENDER->LoadImageFiles(TEXT("Idle_Up"), TEXT("Image/Monster/Player/Idle/Up/Up"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Down"), TEXT("Image/Monster/Player/Idle/Down/Down"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Left"), TEXT("Image/Monster/Player/Idle/Left/Left"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Right"), TEXT("Image/Monster/Player/Idle/Right/Right"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Run_Up"), TEXT("Image/Monster/Player/Run/Up/Up"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Down"), TEXT("Image/Monster/Player/Run/Down/Down"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Left"), TEXT("Image/Monster/Player/Run/Left/Left"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Right"), TEXT("Image/Monster/Player/Run/Right/Right"), TEXT("png"), 3);

		RENDER->LoadImageFiles(TEXT("Attack_Up"), TEXT("Image/Monster/Player/Attack/Up/Up"), TEXT("png"), 2);
		RENDER->LoadImageFiles(TEXT("Attack_Down"), TEXT("Image/Monster/Player/Attack/Down/Down"), TEXT("png"), 2);
		RENDER->LoadImageFiles(TEXT("Attack_Left"), TEXT("Image/Monster/Player/Attack/Left/Left"), TEXT("png"), 2);
		RENDER->LoadImageFiles(TEXT("Attack_Right"), TEXT("Image/Monster/Player/Attack/Right/Right"), TEXT("png"), 2);

		RENDER->LoadImageFiles(TEXT("Attribute_None"), TEXT("Image/Magic/Circle/Normal/Circle_Normal_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Fire"), TEXT("Image/Magic/Circle/Red/Circle_Red_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Water"), TEXT("Image/Magic/Circle/Blue/Circle_Blue_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Electricity"), TEXT("Image/Magic/Circle/Purple/Circle_Purple_"), TEXT("png"), 8);

		RENDER->LoadImageFiles(TEXT("Rune_Fire"), TEXT("Image/Magic/Rune/Fire/Fire"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Rune_Ice"), TEXT("Image/Magic/Rune/Ice/Ice"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Rune_Electricity"), TEXT("Image/Magic/Rune/Electricity/Electricity"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Rune_Bolt"), TEXT("Image/Magic/Rune/Bolt/Bolt"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Rune_Shield"), TEXT("Image/Magic/Rune/Shield/Shield"), TEXT("png"), 7);
		RENDER->LoadImageFiles(TEXT("Rune_Wall"), TEXT("Image/Magic/Rune/Wall/Wall"), TEXT("png"), 7);

		RENDER->LoadImageFiles(TEXT("Correct_Fire"), TEXT("Image/Magic/CorrectType/Fire"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Correct_Ice"), TEXT("Image/Magic/CorrectType/Ice"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Correct_Electricity"), TEXT("Image/Magic/CorrectType/Electricity"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Correct_Bolt"), TEXT("Image/Magic/CorrectType/Bolt"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Correct_Shield"), TEXT("Image/Magic/CorrectType/Shield"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Correct_Wall"), TEXT("Image/Magic/CorrectType/Wall"), TEXT("png"), 1);
		SOUND->LoadFile("Death", "Sound/Effect/Death.wav", false); SOUND->LoadFile("Death", "Sound/Effect/Death.wav", false);

		SOUND->LoadFile("FireCast", "Sound/Cast/FireCast.wav", false);
		SOUND->LoadFile("IceCast", "Sound/Cast/IceCast.wav", false);
		SOUND->LoadFile("ElectricityCast", "Sound/Cast/ElectricityCast.wav", false);
		SOUND->LoadFile("BoltCast", "Sound/Cast/BoltCast.wav", false);
		SOUND->LoadFile("ShieldCast", "Sound/Cast/ShieldCast.wav", false);
		SOUND->LoadFile("WallCast", "Sound/Cast/WallCast.wav", false);

	}

	void Update(float deltaTime)
	{
		Get_Dir_state();
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		case CHARACTER_CAST_ATTRIBUTE: CastingAttributeState(deltaTime); break;
		case CHARACTER_CAST_TYPE: CastingTypeState(deltaTime); break;
		case CHARACTER_CAST_END: EndCastingState(deltaTime); break;
		case CHARACTER_DEATH: DeathState(deltaTime); break;
		}
		Animation()->Update(deltaTime);
		m_rotateDir->Update(deltaTime);
		Animation()->Get(m_attribute)->Update(deltaTime);
		Animation()->Get(m_Rune)->Update(deltaTime);
		m_timer->Update(deltaTime);
		//if (OBJECT->GetPlayer()->GetLife() <= 0.0f)m_state = CHARACTER_DEATH;
	}

	void Draw(Camera* pCamera)
	{

		float opacity=1.0f;
		if (IsHideToWall())opacity = 0.5f;
		pCamera->Draw(Animation()->Current()->GetSprite(), Position(),Vector::Right(),opacity);
		//pCamera->DrawCircle(getCircle().center, getCircle().radius, ColorF::Red, 2.0f);
		//pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
		//Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//pMapCamera->DrawFilledRect(Collider().LeftTop(), Collider().size);

		if (m_state == CHARACTER_CAST_TYPE || m_state == CHARACTER_CAST_END)pCamera->Draw(Animation()->Get(m_attribute)->GetSprite(), Position(), m_rotateDir->GetRotateDir());

		if (m_state == CHARACTER_CAST_END)
		{
			pCamera->Draw(Animation()->Get(m_RuneType)->GetSprite(), Position() + (m_rotateDir->GetRotateDir()*90.0f), Vector::Right(), 1.0f);
			pCamera->Draw(Animation()->Get(m_Rune)->GetSprite(), Position() + (m_rotateDir->GetRotateDir()*-90.0f), Vector::Right(), 1.0f);
		}
		if (m_correct != CORRECT_NONE&&m_state != CHARACTER_IDLE)pCamera->Draw(Animation()->Get(m_correct)->GetSprite(), Position() + Vector(0, -100), Vector::Right(), 0.5f);

		if (m_circleGage >= 2)pCamera->Draw(Animation()->Get(m_Rune)->GetSprite(), Position() + ((Vector(m_rotateDir->GetRotateDir().y, -m_rotateDir->GetRotateDir().x))*90.0f));
		if (m_circleGage >= 3)pCamera->Draw(Animation()->Get(m_Rune)->GetSprite(), Position() + ((Vector(m_rotateDir->GetRotateDir().y, -m_rotateDir->GetRotateDir().x))*-90.0f));
	}

	void IdleState()
	{
		switch (m_dirState)
		{
		case DIR_UP: m_spriteState = IDLE_UP; break;
		case DIR_LEFT: m_spriteState = IDLE_LEFT; break;
		case DIR_RIGHT: m_spriteState = IDLE_RIGHT; break;
		case DIR_DOWN: m_spriteState = IDLE_DOWN; break;
		}

		Animation()->Play(m_spriteState);
		if (UI->Setting() == KEYBOARD)
		{
			if (INPUT->IsKeyPress('W')) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress('S')) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress('A')) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress('D')) { m_state = CHARACTER_RUN; }
		}
		else
		{
			if (INPUT->IsMouseDown(MOUSE_RIGHT)) { m_state = CHARACTER_RUN; }
		}
		//if (INPUT->IsMouseDown(MOUSE_LEFT))OBJECT->CreateSkill(OBJECT->GetPlayer(), USER_PLAYER, FIRE_BOLT);
		if (INPUT->IsKeyDown('1') || INPUT->IsKeyDown('2') || INPUT->IsKeyDown('3'))
		{
			m_state = CHARACTER_CAST_ATTRIBUTE; m_prevAttribute = ATTRIBUTE_WATER; m_correct = CORRECT_ICE;
		}
	}

	void RunState(float deltaTime)
	{
		Move(deltaTime);
		if (INPUT->IsKeyDown('1') || INPUT->IsKeyDown('2') || INPUT->IsKeyDown('3'))
		{
			m_state = CHARACTER_CAST_ATTRIBUTE; m_prevAttribute = ATTRIBUTE_WATER;  m_correct = CORRECT_ICE;
		}
	}

	void CastingAttributeState(float deltaTime)
	{
		Move(deltaTime);
		if (INPUT->IsKeyDown('1')) { m_prevAttribute = ATTRIBUTE_WATER; m_correct = CORRECT_ICE; }
		if (INPUT->IsKeyDown('2')) { m_prevAttribute = ATTRIBUTE_FIRE; m_correct = CORRECT_FIRE; }
		if (INPUT->IsKeyDown('3')) { m_prevAttribute = ATTRIBUTE_ELECTRICITY; m_correct = CORRECT_ELECTRICITY; }

		if (INPUT->IsMouseDown(MOUSE_LEFT) && m_prevAttribute != ATTRIBUTE_NONE)
		{
			m_attribute = m_prevAttribute;
			switch (m_attribute)
			{
			case ATTRIBUTE_FIRE:m_Rune = RUNE_FIRE; break;
			case ATTRIBUTE_WATER:m_Rune = RUNE_ICE; break;
			case ATTRIBUTE_ELECTRICITY:m_Rune = RUNE_ELECTRICITY; break;
			}

			m_prevAttribute = ATTRIBUTE_NONE;
			m_correct = CORRECT_BOLT;
			m_prevSkillType = TYPE_BOLT;

			m_state = CHARACTER_CAST_TYPE;
		}

		if (INPUT->IsKeyDown(VK_TAB))
		{
			m_attribute = ATTRIBUTE_NONE;
			m_prevAttribute = ATTRIBUTE_NONE;
			m_Rune = RUNE_NONE;
			m_RuneType = RUNE_NONE;
			m_circleGage = 1;
			m_checkGage = 0;
			m_state = CHARACTER_IDLE;

		}
	}

	void CastingTypeState(float deltaTime)
	{
		Move(deltaTime);
		if (INPUT->IsKeyDown('1')) { m_prevSkillType = TYPE_BOLT; m_correct = CORRECT_BOLT; }
		if (INPUT->IsKeyDown('2')) { m_prevSkillType = TYPE_SHIELD; m_correct = CORRECT_SHIELD; }
		if (INPUT->IsKeyDown('3')) { m_prevSkillType = TYPE_WALL; m_correct = CORRECT_WALL; }

		if (INPUT->IsMouseDown(MOUSE_LEFT) && m_prevSkillType != TYPE_NONE)
		{
			m_correct = CORRECT_NONE;
			m_skillType = m_prevSkillType;
			m_prevSkillType = TYPE_NONE;
			if (SOUND->FindChannel("FireCast") == NULL&&SOUND->FindChannel("IceCast") == NULL&SOUND->FindChannel("ElectricityCast") == NULL)
			{
				switch (m_attribute)
				{
				case ATTRIBUTE_FIRE:SOUND->Play("FireCast", 2.0f); break;
				case ATTRIBUTE_WATER:SOUND->Play("IceCast", 2.0f); break;
				case ATTRIBUTE_ELECTRICITY:SOUND->Play("ElectricityCast", 2.0f); break;
				}
			}
			switch (m_skillType)
			{
			case TYPE_BOLT:m_RuneType = RUNE_BOLT; break;
			case TYPE_SHIELD:m_RuneType = RUNE_SHIELD; break;
			case TYPE_WALL:m_RuneType = RUNE_WALL; break;
			}

			m_state = CHARACTER_CAST_END;
		}

		if (INPUT->IsKeyDown(VK_TAB))
		{
			m_circleGage = 1;
			m_checkGage = 0;
			m_correct = CORRECT_NONE;
			m_attribute = ATTRIBUTE_NONE;
			m_prevSkillType = TYPE_NONE;
			m_Rune = RUNE_NONE;
			m_RuneType = RUNE_NONE;
			m_state = CHARACTER_IDLE;
		}
	}
	void EndCastingState(float deltaTime)
	{
		

		
		if (!INPUT->IsMouseUp(MOUSE_LEFT))
		{
			m_dir = (RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos()) - Position()).Normalize();
			Get_Dir_state();
			switch (m_dirState)
			{
			case DIR_UP: m_spriteState = ATTACK_UP; break;
			case DIR_LEFT: m_spriteState = ATTACK_LEFT; break;
			case DIR_RIGHT: m_spriteState = ATTACK_RIGHT; break;
			case DIR_DOWN: m_spriteState = ATTACK_DOWN; break;
			}
			Animation()->Play(m_spriteState);
			m_checkGage += deltaTime;
			if (m_checkGage >= 1)
			{
				if (SOUND->FindChannel("FireCast") == NULL&&SOUND->FindChannel("IceCast") == NULL&SOUND->FindChannel("ElectricityCast") == NULL&&m_circleGage < 3)
				{
					switch (m_attribute)
					{
					case ATTRIBUTE_FIRE:SOUND->Play("FireCast", 2.0f); break;
					case ATTRIBUTE_WATER:SOUND->Play("IceCast", 2.0f); break;
					case ATTRIBUTE_ELECTRICITY:SOUND->Play("ElectricityCast", 2.0f); break;
					}
					m_circleGage++;
					m_circleGage = MATH->Clamp(m_circleGage, 1, 3);
					cout << m_circleGage << endl;
				}
				m_checkGage = 0;


			}

		}
		else
		{
			OBJECT->CreateSkill(OBJECT->GetPlayer(), USER_PLAYER, (SKILL_LIST)(m_attribute + m_skillType), m_circleGage);
			m_circleGage = 1;
			m_attribute = ATTRIBUTE_NONE;
			m_correct = CORRECT_NONE;
			m_skillType = TYPE_NONE;
			m_Rune = RUNE_NONE;
			m_RuneType = RUNE_NONE;
			m_state = CHARACTER_IDLE;
		}

	}

	void  DeathState(float deltaTime)
	{
		RENDER->GetCamera(CAM_MAIN)->DrawFilledRect(RENDER->GetCamera(CAM_MAIN)->GetLeftTop(), Vector(800, 600));
		//if (SOUND->FindChannel("Death") == NULL)SOUND->Play("Death", 2.0f);
	}

	void Move(float deltaTime)
	{
		if (UI->NotRun() == false)
		{
			switch (m_dirState)
			{
			case DIR_UP: m_spriteState = RUN_UP; break;
			case DIR_LEFT: m_spriteState = RUN_LEFT; break;
			case DIR_RIGHT: m_spriteState = RUN_RIGHT; break;
			case DIR_DOWN: m_spriteState = RUN_DOWN; break;
			}


			Animation()->Play(m_spriteState);


			Vector prevPos = this->Position();
			Vector movedPos = this->Position();

			//m_dir = Vector::Zero();
			Vector::Zero();

			if (UI->Setting() == MOUSE)
			{
				//if (MATH->SqrDistance(m_targetPos, movedPos) <= 30.0f)m_state = CHARACTER_IDLE;

				if (INPUT->IsMouseDown(MOUSE_RIGHT) || INPUT->IsMousePress(MOUSE_RIGHT) || INPUT->IsMouseDrag(MOUSE_RIGHT) || INPUT->IsMouseUp(MOUSE_RIGHT))
				{

					m_targetPos = RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos());
					m_dir = (m_targetPos - movedPos).Normalize();
					movedPos += m_dir * m_speed * deltaTime;
				}
				else
				{
					m_dir = (m_targetPos - movedPos).Normalize();
					movedPos += m_dir * m_speed * deltaTime;

				}
				if (IsGroundCollided())movedPos = GroundPush(movedPos);
				if (MATH->SqrDistance(m_targetPos, movedPos) >= 30.0f)this->SetPosition(movedPos);
			}

			else
			{
				if (INPUT->IsKeyPress('W'))   m_dir += Vector::Up();
				if (INPUT->IsKeyPress('S'))   m_dir += Vector::Down();
				if (INPUT->IsKeyPress('A'))   m_dir += Vector::Left();
				if (INPUT->IsKeyPress('D'))   m_dir += Vector::Right();


				m_dir = m_dir.Normalize();
				movedPos += m_dir * m_speed * deltaTime;
				if (IsGroundCollided())movedPos = GroundPush(movedPos);
				this->SetPosition(movedPos);
			}

			if (MATH->SqrDistance(prevPos, movedPos) >= 30)
			{
				m_state = CHARACTER_IDLE;
			}
		}



	}
};