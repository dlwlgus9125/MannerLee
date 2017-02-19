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
	Vector SkillSize;
	Vector m_cursor;// 커서 위치

public:
	FieldScene()
	{
		RENDER->CreateCamera(CAM_MAIN, 860 * 2.0f, 1100 * 2.0f, VIEW_WIDTH, VIEW_HEIGHT);
		//RENDER->CreateCamera(CAM_MAP, 2000, 3000, 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));
		
		OBJECT->CreatePlayer(Vector(620, 2200), 30);

		
	}

	void OnEnter()
	{
		SOUND->Resume("DungeonBgm");
		OBJECT->GetPlayer()->SetPosition(Vector(500, 1650));
		OBJECT->GetPlayer()->SetDir(Vector::Up());
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 2.0f, 0, 0));
		//m_pBg->SetSize(860 * 2.0f, 1100 * 2.0f);
		OBJECT->CreateBoss(OBJ_BOSS, Vector(885, 400), 50);
		OBJECT->GetPlayer()->setFadeOut(false);
		
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
		OBJECT->CreateProps(OBJ_GROUND, Vector(560, 1460), Vector(320, 120));
		OBJECT->CreateProps(OBJ_GROUND, Vector(400, 1700), Vector(70, 360));
		OBJECT->CreateProps(OBJ_GROUND, Vector(850, 1900), Vector(1000, 100));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1200, 1460), Vector(320, 120));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1370, 1700), Vector(70, 360));

		OBJECT->CreateProps(OBJ_HIDE, Vector(280, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(350, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(420, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(490, 840)*1.33f, Vector(10, 10)*1.33f);

		OBJECT->CreateProps(OBJ_HIDE, Vector(830, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(900, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(970, 840)*1.33f, Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1045, 840)*1.33f, Vector(10, 10)*1.33f);

		OBJECT->CreateProps(OBJ_HIDE, Vector(530, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(620, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(720, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(880, 1810), Vector(100, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1040, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1135, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1230, 1810), Vector(10, 10)*1.33f);
		OBJECT->CreateProps(OBJ_HIDE, Vector(1330, 1810), Vector(10, 10)*1.33f);

		OBJECT->CreateProps(OBJ_CHECKER, Vector(885, 840), Vector(800,50));
		//OBJECT->CreateProps(OBJ_GROUND, Vector(750, 1150), Vector(190, 230));
	}

	void OnUpdate(float deltaTime)
	{
		

		cout << RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos()).x << ", " << RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos()).y << endl;
		if (MATH->IsCollided(OBJECT->GetPlayer()->getCircle(), OBJECT->GetProps(OBJ_CHECKER)->Collider())&&OBJECT->GetPlayer()->isComeBossMap() == false)
		{
			if (SOUND->FindChannel("BossVoice") == NULL&&OBJECT->GetPlayer()->isComeBossMap() == false)SOUND->Play("BossVoice", 2.0f);
			if (SOUND->FindChannel("DungeonBgm") != NULL)SOUND->Stop("DungeonBgm");
			if (SOUND->FindChannel("BossBgm") == NULL)SOUND->Play("BossBgm", 0.5f);
			


			OBJECT->GetPlayer()->setIscome(true);
			OBJECT->CreateSkill(OBJECT->GetMonster(OBJ_BOSS), USER_MINION, ETERNAL_FIRE_WALL);
			cout << OBJECT->GetPlayer()->isComeBossMap() << endl;
			OBJECT->CreateProps(OBJ_GROUND, Vector(885, 950), Vector(800, 50));
		}


		
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
			if (MATH->IsCollided(m_cursor, Vector(634, 10), Vector(690, 63))) //포션
			{
				cout << "test" << endl;

				OBJECT->GetPlayer()->SetLife(-UI->EatPotion());
				UI->SetNotRun(true);
			}

			else if (MATH->IsCollided(m_cursor, Vector(710, 10), Vector(766, 63))) // 설정
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
		if (INPUT->IsKeyPress(VK_LEFT)) OBJECT->GetPlayer()->SetLife(10);
		if (INPUT->IsKeyPress(VK_RIGHT)) OBJECT->GetPlayer()->SetLife(-10);




		if (OBJECT->GetPlayer()->GetLife() <= 0.0f)
		{
			OBJECT->GetPlayer()->setFadeOut(true);
			if (OBJECT->GetPlayer()->getFadeOut() >= 1.0f)SCENE->ChangeScene(SCENE_DEATH);
		}
	}

	void OnExit()
	{
		SOUND->Stop("IntroBgm");
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		UI->Draw(OBJECT->GetPlayer()->MaxLife(), OBJECT->GetPlayer()->GetLife());
		UI->DrawSetting();
		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}


};