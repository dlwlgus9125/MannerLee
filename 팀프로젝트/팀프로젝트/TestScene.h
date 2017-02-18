#pragma once
#include <stdio.h>
#include <Windows.h>
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "Common.h"
#include "InputManager.h"
#include <vector>

#pragma warning(disable: 4996)

using namespace std;

struct MBOX
{
	Vector Standard;
	Vector size;

	MBOX() {}
	MBOX(Vector LeftTop, Vector RightBottom)
	{
		this->Standard = LeftTop;
		this->size = RightBottom;
	}

	Vector LeftTop() { return this->Standard; }
	Vector RightBottom() { return this->size; }
	Vector LeftBottom() { return Vector(Standard.x, size.y); }
	Vector RightTop() { return Vector(size.x, Standard.y); }
	Vector MBCenter() { return Vector((LeftTop().x + (RightTop().x - LeftTop().x) / 2), LeftTop().y+((RightBottom().y - LeftTop().y) / 2)); }
	Vector Size() { return Vector((Standard.x - size.x), (Standard.y - size.y)); }
};

class TestScene : public IScene
{
	Sprite* m_pBg;
	Vector m_Cursor;// 커서 위치
	Vector m_Center;
	Vector m_Standard;
	Vector m_Draw;
	MBOX* m_Box[100];
	int m_count;

	FILE *fp;

public:
	TestScene()
	{
		FILE *fp = NULL;
		m_count = 0;
		m_Center = { 400.0f, 300.0f };
		RENDER->SetChange(CAM_MAIN, 860 * 2.0f, 1100 * 2.0f, VIEW_WIDTH, VIEW_HEIGHT);
	}

	void OnEnter()
	{
		fp = fopen("Test.txt", "w");
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 2.0f, 0, 0));


		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, 800, 600);


	}

	void OnUpdate(float deltaTime)
	{

		m_Center.x = MATH->Clamp(m_Center.x, 400.0f, 800.0f);
		m_Center.y = MATH->Clamp(m_Center.y, 300.0f, 2900.0f);

		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(m_Center);

		if (INPUT->IsKeyUp(VK_LEFT))
		{
			m_Center.x -= 100.0f;
		}
		
		if (INPUT->IsKeyUp(VK_RIGHT))
		{
			m_Center.x += 100.0f;
		}

		if (INPUT->IsKeyUp(VK_UP))
		{
			m_Center.y -= 100.0f;
		}


		if (INPUT->IsKeyUp(VK_DOWN))
		{
			m_Center.y += 100.0f;
		}

		if (INPUT->IsMouseUp(MOUSE_LEFT))
		{
			m_Cursor = INPUT->GetMousePos();
			m_Standard = GetBGPos();

			cout << m_Cursor.x << ", " << m_Cursor.y << " ㅁㅁㅁ " << m_Center.x << ", " << m_Center.y << endl;
			cout << m_Standard.x << ", " << m_Standard.y << endl;
			cout << m_Draw.x << ", " << m_Draw.y << endl;
		}

		if (INPUT->IsMouseUp(MOUSE_RIGHT))
		{
			m_Cursor = INPUT->GetMousePos();
			m_Draw = GetBGPos();
			cout << m_Cursor.x << ", " << m_Cursor.y << " ㅁㅁㅁ " << m_Center.x << ", " << m_Center.y << endl;
			cout << m_Standard.x << ", " << m_Standard.y << endl;
			cout << m_Draw.x << ", " << m_Draw.y << endl;
		}

		if (INPUT->IsKeyUp(VK_BACK))
		{
			m_Standard.x = NULL;
			m_Standard.y = NULL;

			m_Draw.x = NULL;
			m_Draw.y = NULL;
			m_Box[m_count--] = NULL;

			cout << m_Cursor.x << ", " << m_Cursor.y << " ㅁㅁㅁ " << m_Center.x << ", " << m_Center.y << endl;
			cout << m_Standard.x << ", " << m_Standard.y << endl;
			cout << m_Draw.x << ", " << m_Draw.y << endl;
		}

		if (INPUT->IsKeyUp(VK_RETURN))
		{
			m_Box[m_count++] = new MBOX(m_Standard, m_Draw);
		}

		if (INPUT->IsKeyUp(VK_ESCAPE))
		{
			for (int i = 0; i < m_count; i++)
			{
				fprintf(fp, "OBJECT->CreateProps(OBJ_GROUND, Vector(%.0f, %.0f), Vector(%.0f, %.0f)); \n", m_Box[i]->MBCenter().x, m_Box[i]->MBCenter().y, m_Box[i]->Size().x, m_Box[i]->Size().y);
				PostQuitMessage(0);
			}
		}
	}

	void OnExit()
	{
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);

		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);

		for (int i = 0; i < m_count; i++)
		{
			OBJECT->CreateProps(OBJ_GROUND, m_Box[m_count - 1]->MBCenter(), m_Box[m_count - 1]->Size());
		}

	}

	Vector GetBGPos()
	{
		Vector pos;
		pos.x = ((m_Center.x - 400.0f) + m_Cursor.x);
		pos.y = ((m_Center.y - 300.0f) + m_Cursor.y);
		return pos;
	}
	
};
