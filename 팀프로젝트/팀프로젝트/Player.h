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

		RENDER->LoadImageFiles(TEXT("Idle_Up"), TEXT("Image/Monster/Player/Idle/Up/Up"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Down"), TEXT("Image/Monster/Player/Idle/Down/Down"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Left"), TEXT("Image/Monster/Player/Idle/Left/Left"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Right"), TEXT("Image/Monster/Player/Idle/Right/Right"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Run_Up"), TEXT("Image/Monster/Player/Run/Up/Up"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Down"), TEXT("Image/Monster/Player/Run/Down/Down"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Left"), TEXT("Image/Monster/Player/Run/Left/Left"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Right"), TEXT("Image/Monster/Player/Run/Right/Right"), TEXT("png"), 3);

		RENDER->LoadImageFiles(TEXT("Attribute_None"), TEXT("Image/Magic/Circle/Normal/Circle_Normal_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Fire"), TEXT("Image/Magic/Circle/Red/Circle_Red_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Water"), TEXT("Image/Magic/Circle/Blue/Circle_Blue_"), TEXT("png"), 8);
		RENDER->LoadImageFiles(TEXT("Attribute_Electricity"), TEXT("Image/Magic/Circle/Purple/Circle_Purple_"), TEXT("png"), 8);

		SOUND->LoadFile("Death", "Sound/Effect/Death.wav", false);

		SOUND->LoadFile("FireCast", "Sound/Cast/FireCast.wav", false);
		SOUND->LoadFile("IceCast", "Sound/Cast/IceCast.wav", false);
		SOUND->LoadFile("ElectricityCast", "Sound/Cast/ElectricityCast.wav", false);
		SOUND->LoadFile("BoltCast", "Sound/Cast/BoltCast.wav", false);
		SOUND->LoadFile("ShieldCast", "Sound/Cast/ShieldCast.wav", false);
		SOUND->LoadFile("WallCast", "Sound/Cast/WallCast.wav", false);

	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		case CHARACTER_CAST_ATTRIBUTE: CastingAttributeState(deltaTime); break;
		case CHARACTER_CAST_TYPE: CastingTypeState(deltaTime); break;
		case CHARACTER_CAST_END: EndCastingState(deltaTime); break;
		case CHARACTER_DEATH: DeathState(deltaTime); break;
		}
		Get_Dir_state();

		Animation()->Update(deltaTime);
		m_rotateDir->Update(deltaTime);
		Animation()->Get(m_attribute)->Update(deltaTime);
		m_timer->Update(deltaTime);
		//if (OBJECT->GetPlayer()->GetLife() <= 0.0f)m_state = CHARACTER_DEATH;
	}

	void Draw(Camera* pCamera)
	{
		if (IsHideToWall())Animation()->Current()->GetSprite()->SetOpacity(0.5f);
		pCamera->Draw(Animation()->Current()->GetSprite(), Position());
		//pCamera->DrawCircle(getCircle().center, getCircle().radius, ColorF::Red, 2.0f);
		//pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		pCamera->DrawLine(Position() + 15.0f, Position() + 15.0f + m_dir * 30, ColorF::Blue, 3);
		//Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//pMapCamera->DrawFilledRect(Collider().LeftTop(), Collider().size);

		if (m_state == CHARACTER_CAST_ATTRIBUTE || m_state == CHARACTER_CAST_TYPE)pCamera->Draw(Animation()->Get(m_attribute)->GetSprite(), Position(), m_rotateDir->GetRotateDir());
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
			if (INPUT->IsKeyPress(VK_LEFT)) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress(VK_RIGHT)) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress(VK_UP)) { m_state = CHARACTER_RUN; }
			if (INPUT->IsKeyPress(VK_DOWN)) { m_state = CHARACTER_RUN; }
		}
		else
		{
			if (INPUT->IsMouseDown(MOUSE_LEFT)) { m_state = CHARACTER_RUN; }
		}
		if (INPUT->IsKeyDown('E')) { m_state = CHARACTER_CAST_ATTRIBUTE; }
	}

	void RunState(float deltaTime)
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

			m_dir = Vector::Zero();


			if (UI->Setting() == MOUSE)
			{
				Vector targetPos = RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos());

				if (MATH->SqrDistance(targetPos, movedPos) <= 30.0f)m_state = CHARACTER_IDLE;
				m_dir = (targetPos - movedPos).Normalize();

				if (!INPUT->IsMouseUp(MOUSE_LEFT))
				{

					movedPos += m_dir * m_speed * deltaTime;
					if (IsGroundCollided())movedPos = GroundPush(movedPos);
					this->SetPosition(movedPos);
				}
			}

			else
			{
				if (INPUT->IsKeyPress(VK_LEFT)) m_dir += Vector::Left();
				if (INPUT->IsKeyPress(VK_RIGHT)) m_dir += Vector::Right();
				if (INPUT->IsKeyPress(VK_UP)) m_dir += Vector::Up();
				if (INPUT->IsKeyPress(VK_DOWN)) m_dir += Vector::Down();
				m_dir = m_dir.Normalize();
				movedPos += m_dir * m_speed * deltaTime;
				this->SetPosition(movedPos);

				float x1 = OBJECT->GetPlayer()->Position().x;
				float y1 = OBJECT->GetPlayer()->Position().y;

				float x2 = RENDER->GetCamera(CAM_MAIN)->GetPos().x;
				float y2 = RENDER->GetCamera(CAM_MAIN)->GetPos().y;
			}

			if (MATH->SqrDistance(prevPos, movedPos) == 0)
			{
				m_state = CHARACTER_IDLE;
			}
		}
		if (INPUT->IsKeyDown('E')) { m_state = CHARACTER_CAST_ATTRIBUTE; }
	}

	void CastingAttributeState(float deltaTime)
	{
		if (INPUT->IsKeyDown('1'))m_prevAttribute = ATTRIBUTE_FIRE;
		if (INPUT->IsKeyDown('2'))m_prevAttribute = ATTRIBUTE_WATER;
		if (INPUT->IsKeyDown('3'))m_prevAttribute = ATTRIBUTE_ELECTRICITY;

		if (INPUT->IsKeyDown('E') && m_prevAttribute != ATTRIBUTE_NONE)
		{
			m_attribute = m_prevAttribute;
			m_prevAttribute = ATTRIBUTE_NONE;
			m_state = CHARACTER_CAST_TYPE;
		}

		if (INPUT->IsKeyDown(VK_TAB))
		{
			m_attribute = ATTRIBUTE_NONE;
			m_prevAttribute = ATTRIBUTE_NONE;
			m_state = CHARACTER_IDLE;
		}
	}

	void CastingTypeState(float deltaTime)
	{
		if (INPUT->IsKeyDown('1'))m_prevSkillType = TYPE_BOLT;
		if (INPUT->IsKeyDown('2'))m_prevSkillType = TYPE_SHIELD;
		if (INPUT->IsKeyDown('3'))m_prevSkillType = TYPE_WALL;

		if (INPUT->IsKeyDown('E') && m_prevSkillType != TYPE_NONE)
		{
			m_skillType = m_prevSkillType;
			m_prevSkillType = TYPE_NONE;
			switch (m_attribute)
			{
			case ATTRIBUTE_FIRE:SOUND->Play("FireCast", 2.0f); cout << "test" << endl; break;
			case ATTRIBUTE_WATER:SOUND->Play("IceCast", 2.0f); break;
			case ATTRIBUTE_ELECTRICITY:SOUND->Play("ElectricityCast", 2.0f); break;
			}
			m_state = CHARACTER_CAST_END;
		}

		if (INPUT->IsKeyDown(VK_TAB))
		{
			m_attribute = ATTRIBUTE_NONE;
			m_prevSkillType = TYPE_NONE;
			m_state = CHARACTER_IDLE;
		}
	}
	void EndCastingState(float deltaTime)
	{
		if (SOUND->FindChannel("FireCast") == NULL&&SOUND->FindChannel("IceCast") == NULL&SOUND->FindChannel("ElectricityCast") == NULL)
		{
			switch (m_skillType)
			{
			case TYPE_BOLT:SOUND->Play("BoltCast", 2.0f); break;
			case TYPE_SHIELD:SOUND->Play("ShieldCast", 2.0f); break;
			case TYPE_WALL:SOUND->Play("WallCast", 2.0f); break;
			}
			OBJECT->CreateSkill(OBJECT->GetPlayer(), USER_PLAYER, (SKILL_LIST)(m_attribute + m_skillType));
			m_attribute = ATTRIBUTE_NONE;
			m_skillType = TYPE_NONE;
			m_state = CHARACTER_IDLE;
		}
	}

	void  DeathState(float deltaTime)
	{
		RENDER->GetCamera(CAM_MAIN)->DrawFilledRect(RENDER->GetCamera(CAM_MAIN)->GetLeftTop(), Vector(800, 600));
		if (SOUND->FindChannel("Death") == NULL)SOUND->Play("Death", 2.0f);
	}

};