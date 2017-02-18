#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "Common.h"


class FieldScene : public IScene
{
	Sprite* m_pBg;
	float MaxHp;
	float CurrentHp;
	Vector SkillSize;
	Vector m_cursor;// Ŀ�� ��ġ

public:
	FieldScene()
	{
		MaxHp = 1000.0f;
		CurrentHp = 800.0f;
		
		RENDER->SetChange(CAM_MAIN, 860 * 2.0f, 1100 * 2.0f, VIEW_WIDTH, VIEW_HEIGHT);
		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));
		//SOUND->LoadFile("IntroBgm", "Sound/Intro.wav", true);
		//SOUND->LoadFile("Boss1Bgm", "Sound/Boss1.wav", true);
		//SOUND->LoadFile("Explosion1", "Sound/Effect/Explosion1.wav", false);
		//OBJECT->CreateSkill(OBJECT->GetPlayer(), USER_PLAYER, Vector());

		OBJECT->CreateMonster(OBJ_MONSTER, MONSTER_MINION_RED, Vector(600, 600), 30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 2.0f, 0, 0));
		//m_pBg->SetSize(860 * 2.0f, 1100 * 2.0f);
		//SOUND->Play("IntroBgm", 0.5f);
		//RENDER->GetCamera(CAM_MAP)->SetScreenRect(0, 0, 200, 200);

		OBJECT->CreateProps(OBJ_GROUND, Vector(320, 370)*1.33f, Vector(100, 670)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(650, 80)*1.33f, Vector(600, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(1010, 370)*1.33f, Vector(100, 670)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(220, 800)*1.33f, Vector(100, 200)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(410, 900)*1.33f, Vector(280, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(1100, 800)*1.33f, Vector(100, 200)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(930, 900)*1.33f, Vector(280, 100)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(760, 1000)*1.33f, Vector(50, 360)*1.33f);
		OBJECT->CreateProps(OBJ_GROUND, Vector(575, 1000)*1.33f, Vector(50, 360)*1.33f);

		OBJECT->CreateProps(OBJ_HIDE, Vector(280, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(350, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(420, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(490, 840)*1.33f, Vector(10, 10)*1.33f);

		OBJECT->CreateProps(OBJ_HIDE, Vector(830, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(900, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(970, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1045, 840)*1.33f, Vector(10, 10)*1.33f);
		//OBJECT->CreateProps(OBJ_GROUND, Vector(750, 1150), Vector(190, 230));
	}

	void OnUpdate(float deltaTime)
	{
		m_cursor = INPUT->GetMousePos();
		OBJECT->Update(deltaTime);
		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(OBJECT->GetPlayer()->Position());
	
		if (INPUT->IsKeyDown(VK_TAB))RENDER->GetCamera(CAM_MAIN)->SetIsWaveTrue();
		if (RENDER->GetCamera(CAM_MAIN)->GetIsWave())
		{
			RENDER->GetCamera(CAM_MAIN)->ShakingCamera(5);
		}

		if (INPUT->IsMouseDown(MOUSE_LEFT))
		{
			if (MATH->IsCollided(m_cursor, Vector(634, 10), Vector(690, 63))) //����
			{

				CurrentHp += UI->EatPotion();
				UI->SetNotRun(true);
			}

			else if (MATH->IsCollided(m_cursor, Vector(710, 10), Vector(766, 63))) // ����
			{
				UI->SetSettingDraw(true);
				UI->SetNotRun(true);
			}

			else if (UI->SettingDraw())
			{
				if (MATH->IsCollided(m_cursor, Vector(494, 197), Vector(532, 238)))
				{
					UI->SetKey(KEYBOARD);
				}
				
				else if (MATH->IsCollided(m_cursor, Vector(494, 272), Vector(532, 313)))
				{
					UI->SetKey(MOUSE);
				}

				else if (MATH->IsCollided(m_cursor, Vector(590, 144), Vector(632, 187)))
				{
					UI->SetSettingDraw(false);
				}

				else if (MATH->IsCollided(m_cursor, Vector(494, 344), Vector(532, 385)))
				{
					PostQuitMessage(0);
				}

			}

		}

		if (UI->SettingDraw() == false)
		{
			UI->SetNotRun(false);
		}
		//if (INPUT->IsKeyPress(VK_LEFT)) CurrentHp -= 8;
		//if (INPUT->IsKeyPress(VK_RIGHT)) CurrentHp += 8;





	}

	void OnExit()
	{
		/*SOUND->Stop("IntroBgm");*/
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		UI->Draw(MaxHp, CurrentHp);
		UI->DrawSetting();
		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}
};