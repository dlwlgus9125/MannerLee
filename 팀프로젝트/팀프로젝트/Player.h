#pragma once
#include "Character.h"
#include "UIManager.h"

class Player : public Character
{
	Timer* m_timer;
	


public:
	Player(int id) : Character(id)
	{
		m_state = CHARACTER_IDLE;
		m_dir = Vector::Down();
		m_dirState = DIR_DOWN;
		m_speed = 150;
		m_timer = new Timer();

		RENDER->LoadImageFiles(TEXT("Idle_Up"), TEXT("Image/Monster/Player/Idle/Up/Up"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Down"), TEXT("Image/Monster/Player/Idle/Down/Down"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Left"), TEXT("Image/Monster/Player/Idle/Left/Left"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Right"), TEXT("Image/Monster/Player/Idle/Right/Right"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Run_Up"), TEXT("Image/Monster/Player/Run/Up/Up"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Down"), TEXT("Image/Monster/Player/Run/Down/Down"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Left"), TEXT("Image/Monster/Player/Run/Left/Left"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Right"), TEXT("Image/Monster/Player/Run/Right/Right"), TEXT("png"), 3);
	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		}
		Get_Dir_state();
		
		Animation()->Update(deltaTime);
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
			if(INPUT->IsMouseDown(MOUSE_LEFT)) { m_state = CHARACTER_RUN; }
		}
		
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

	}

	void CastAttributeCircle()
	{


	}



};