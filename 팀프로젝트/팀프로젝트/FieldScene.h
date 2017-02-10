#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "Common.h"



class FieldScene : public IScene
{
	Sprite* m_pBg;
	float MaxHp;
	float CurrentHp;
	Vector SkillSize;
	Vector m_cursor;// 커서 위치
public:
	FieldScene()
	{
		MaxHp = 1000.0f;
		CurrentHp = 800.0f;
		RENDER->CreateCamera(CAM_MAIN, 860 * 2.0f, 1100 * 2.0f, VIEW_WIDTH, VIEW_HEIGHT);
		//RENDER->CreateCamera(CAM_MAP, 2000, 3000, 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));

		RENDER->LoadImageFiles(TEXT("Idle_Up"), TEXT("Image/Monster/Player/Idle/Up/Up"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Down"), TEXT("Image/Monster/Player/Idle/Down/Down"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Left"), TEXT("Image/Monster/Player/Idle/Left/Left"), TEXT("png"), 1);
		RENDER->LoadImageFiles(TEXT("Idle_Right"), TEXT("Image/Monster/Player/Idle/Right/Right"), TEXT("png"), 1);

		RENDER->LoadImageFiles(TEXT("Run_Up"), TEXT("Image/Monster/Player/Run/Up/Run_Up"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Down"), TEXT("Image/Monster/Player/Run/Down/Run_Down"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Left"), TEXT("Image/Monster/Player/Run/Left/Run_Left"), TEXT("png"), 3);
		RENDER->LoadImageFiles(TEXT("Run_Right"), TEXT("Image/Monster/Player/Run/Right/Run_Right"), TEXT("png"), 3);

		OBJECT->CreatePlayer(Vector(600, 800), 30);
		OBJECT->CreateSkill(OBJECT->GetPlayer(), SKILL_NONE, SkillSize);

		OBJECT->CreateMonster(OBJ_MONSTER, Vector(600, 600), 30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 1.0f, 0, 0));
		m_pBg->SetSize(860 * 2.0f, 1100 * 2.0f);

		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, 800, 600);
		//RENDER->GetCamera(CAM_MAP)->SetScreenRect(0, 0, 200, 200);

		OBJECT->CreateProps(OBJ_GROUND, Vector(280, 370)*1.33f, Vector(100, 670)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(630, 50)*1.33f, Vector(600, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(950, 370)*1.33f, Vector(100, 670)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(180, 800)*1.33f, Vector(100, 200)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(370, 900)*1.33f, Vector(280, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(1050, 800)*1.33f, Vector(100, 200)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(890, 900)*1.33f, Vector(280, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(725, 1000)*1.33f, Vector(50, 360)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(520, 1000)*1.33f, Vector(50, 360)*1.33f);
		//OBJECT->CreateProps(OBJ_GROUND, Vector(750, 1150), Vector(190, 230));
	}

	void OnUpdate(float deltaTime)
	{
		m_cursor = INPUT->GetMousePos();
		OBJECT->Update(deltaTime);
		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(OBJECT->GetPlayer()->Position());
		bool test = false;

		if (test)
		{
			int t = (int)timeGetTime() / 5 % 30 % 2;
			int z = (int)timeGetTime() / 5 % 30 % 7;
			int reverse1 = 7 - z;
			//cout << t << endl;
			//cout << z << endl;
			float y = sin(z*1.0f) * powf(1.0f, z);
			float reverse2 = sin(reverse1*1.0f) * powf(0.5f, reverse1);
			cout << y << endl;
			if (t == 0)RENDER->GetCamera(CAM_MAIN)->SetCenterPos(Vector(OBJECT->GetPlayer()->Position().x + y * 20, OBJECT->GetPlayer()->Position().y + reverse2 * 20));
			if (t == 1)RENDER->GetCamera(CAM_MAIN)->SetCenterPos(Vector(OBJECT->GetPlayer()->Position().x + reverse2 * 20, OBJECT->GetPlayer()->Position().y + y * 20));
		}

		if (INPUT->IsMouseDown(MOUSE_LEFT))
		{
			if (MATH->IsCollided(m_cursor, Vector(634, 10), Vector(690, 63)))
			{
				CurrentHp += UI->EatPotion();
				UI->SetNotRun(true);
			}
			else
			{
				UI->SetNotRun(false);
			}
		}
		if (INPUT->IsKeyPress(VK_LEFT)) CurrentHp -= 8;
		if (INPUT->IsKeyPress(VK_RIGHT)) CurrentHp += 8;


		float t = deltaTime * 1000;



	}

	void OnExit()
	{
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		UI->Draw(MaxHp, CurrentHp);
		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}
};