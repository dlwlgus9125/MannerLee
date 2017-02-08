#pragma once
#include "Character.h"

class Player : public Character
{
	CHARACTER_STATE m_state;
	Vector m_dir;
	float m_speed;


public:
	Player(int id) : Character(id)
	{
		m_state = CHARACTER_IDLE;
		m_dir = Vector::Down();
		m_speed = 300;

	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case CHARACTER_IDLE: IdleState(); break;
		case CHARACTER_RUN: RunState(deltaTime); break;
		}
	}

	void Draw(Camera* pCamera)
	{
		/*pCamera->Draw(Animation()->Current()->GetSprite(), Position(), -1);
		pCamera->DrawRect(Collider().LeftTop(), Collider().size);
		pCamera->DrawRect(m_punchCollider.LeftTop(), m_punchCollider.size);*/
		pCamera->DrawCircle(getCircle().center, getCircle().radius, ColorF::Red, 2.0f);
		pCamera->DrawFillCircle(Position(), 30, ColorF::Red);
		pCamera->DrawLine(Position()+15.0f , Position()+15.0f + m_dir * 30, ColorF::Blue, 3);
		//Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//pMapCamera->DrawFilledRect(Collider().LeftTop(), Collider().size);
	}

	void IdleState()
	{
		/*if (INPUT->IsKeyPress(VK_LEFT)) { m_state = CHARACTER_RUN; }
		if (INPUT->IsKeyPress(VK_RIGHT)) { m_state = CHARACTER_RUN; }
		if (INPUT->IsKeyPress(VK_UP)) { m_state = CHARACTER_RUN; }
		if (INPUT->IsKeyPress(VK_DOWN)) { m_state = CHARACTER_RUN; }*/

		if (INPUT->IsMouseDown(MOUSE_LEFT)) { m_state = CHARACTER_RUN; }
	}

	void RunState(float deltaTime)
	{
		Vector prevPos = this->Position();
		Vector movedPos = this->Position();

		m_dir = Vector::Zero();
		Vector targetPos = RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos());


		
		if (MATH->SqrDistance(targetPos, movedPos) <= 30.0f)m_state = CHARACTER_IDLE;
		m_dir = (targetPos - movedPos).Normalize();


		if (!INPUT->IsMouseUp(MOUSE_LEFT))
		{
			movedPos += m_dir * m_speed * deltaTime;
			this->SetPosition(movedPos);
		}

		/*m_dir = Vector::Zero();
		if (INPUT->IsKeyPress(VK_LEFT)) m_dir += Vector::Left();
		if (INPUT->IsKeyPress(VK_RIGHT)) m_dir += Vector::Right();
		if (INPUT->IsKeyPress(VK_UP)) m_dir += Vector::Up();
		if (INPUT->IsKeyPress(VK_DOWN)) m_dir += Vector::Down();
		m_dir = m_dir.Normalize();
		movedPos += m_dir * m_speed * deltaTime;
		this->SetPosition(movedPos);*/

		/*float x1 = OBJECT->GetPlayer()->Position().x;
		float y1 = OBJECT->GetPlayer()->Position().y;

		cout << "플레이어 x : " << x1 << "   y : " << y1 << endl;
		float x2 = RENDER->GetCamera(CAM_MAIN)->GetPos().x;
		float y2 = RENDER->GetCamera(CAM_MAIN)->GetPos().y;
		cout << "카메라 x : " << x2 << "   y : " << y2 << endl;
		cout << "원 센터 x: " << getCircle().center.x << "원 센터 y: " << getCircle().center.y << endl;
*/
		if (MATH->SqrDistance(prevPos, movedPos) == 0)
		{
			m_state = CHARACTER_IDLE;
		}
		if (IsGroundCollided()) this->SetPosition(prevPos);
	}

	
};