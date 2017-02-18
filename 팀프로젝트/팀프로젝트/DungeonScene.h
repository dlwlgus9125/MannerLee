#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "Common.h"
#include "InputManager.h"



class DungeonScene : public IScene
{
	Sprite* m_DungeonBg;
	float MaxHp;
	float CurrentHp;
	Vector SkillSize;
	Vector m_cursor;// 커서 위치

public:
	DungeonScene()
	{
		MaxHp = 1000.0f;
		CurrentHp = 800.0f;
		RENDER->CreateCamera(CAM_MAIN, 1200, 3129, VIEW_WIDTH, VIEW_HEIGHT);

		RENDER->LoadImageFile(TEXT("Dungeon"), TEXT("Image/Map/Castle.png"));


		OBJECT->CreatePlayer(Vector(620, 2500), 30);
		//OBJECT->CreateSkill(OBJECT->GetPlayer(), USER_PLAYER, Vector());

		OBJECT->CreateMonster(OBJ_MONSTER, MONSTER_MINION_RED, Vector(620, 3000), 30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_DungeonBg, Sprite(RENDER->GetImage(TEXT("Dungeon")), 1.0f, 0, 0));
		m_DungeonBg->SetSize(1200, 3129);
		//SOUND->Play("IntroBgm", 0.5f);

		OBJECT->CreateProps(OBJ_GROUND, Vector(898, 46), Vector(-339, -63));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1055, 240), Vector(-45, -318));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1001, 429), Vector(-161, -107));
		OBJECT->CreateProps(OBJ_GROUND, Vector(763, 424), Vector(-172, -120));
		OBJECT->CreateProps(OBJ_GROUND, Vector(710, 211), Vector(-63, -300));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1043, 683), Vector(-262, 405));
		OBJECT->CreateProps(OBJ_GROUND, Vector(825, 688), Vector(54, 405));
		OBJECT->CreateProps(OBJ_GROUND, Vector(624, 692), Vector(345, 176));
		OBJECT->CreateProps(OBJ_GROUND, Vector(336, 804), Vector(234, 170));
		OBJECT->CreateProps(OBJ_GROUND, Vector(626, 807), Vector(-115, -119));
		OBJECT->CreateProps(OBJ_GROUND, Vector(171, 1267), Vector(102, 1094));
		OBJECT->CreateProps(OBJ_GROUND, Vector(255, 1252), Vector(-60, -309));
		OBJECT->CreateProps(OBJ_GROUND, Vector(368, 1361), Vector(-51, -655));
		OBJECT->CreateProps(OBJ_GROUND, Vector(253, 1590), Vector(-62, -190));
		OBJECT->CreateProps(OBJ_GROUND, Vector(480, 1690), Vector(-55, -103));
		OBJECT->CreateProps(OBJ_GROUND, Vector(766, 1634), Vector(-52, -104));
		OBJECT->CreateProps(OBJ_GROUND, Vector(437, 1985), Vector(253, 117));
		OBJECT->CreateProps(OBJ_GROUND, Vector(801, 1978), Vector(-230, -104));
		OBJECT->CreateProps(OBJ_GROUND, Vector(988, 1909), Vector(-141, -196));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1062, 1266), Vector(-65, 1081));
		OBJECT->CreateProps(OBJ_GROUND, Vector(882, 1363), Vector(-52, -652));
		OBJECT->CreateProps(OBJ_GROUND, Vector(999, 1591), Vector(-55, -198));
		OBJECT->CreateProps(OBJ_GROUND, Vector(998, 1249), Vector(-58, -313));
		OBJECT->CreateProps(OBJ_GROUND, Vector(937, 1353), Vector(-60, -105));
		OBJECT->CreateProps(OBJ_GROUND, Vector(512, 2208), Vector(65, 325));
		OBJECT->CreateProps(OBJ_GROUND, Vector(757, 2197), Vector(-76, 334));
		OBJECT->CreateProps(OBJ_GROUND, Vector(280, 1869), Vector(-114, -113));
		OBJECT->CreateProps(OBJ_GROUND, Vector(833, 2323), Vector(-109, 220));
		OBJECT->CreateProps(OBJ_GROUND, Vector(948, 2376), Vector(-113, 223));
		OBJECT->CreateProps(OBJ_GROUND, Vector(910, 2488), Vector(-46, -96));
		OBJECT->CreateProps(OBJ_GROUND, Vector(801, 2643), Vector(-55, -131));
		OBJECT->CreateProps(OBJ_GROUND, Vector(459, 2646), Vector(-55, -141));
		OBJECT->CreateProps(OBJ_GROUND, Vector(425, 2322), Vector(-119, -219));
		OBJECT->CreateProps(OBJ_GROUND, Vector(312, 2374), Vector(-114, -226));
		OBJECT->CreateProps(OBJ_GROUND, Vector(222, 2757), Vector(63, -538));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1039, 2657), Vector(-71, -780));
		OBJECT->CreateProps(OBJ_GROUND, Vector(382, 3012), Vector(312, 112));
		OBJECT->CreateProps(OBJ_GROUND, Vector(868, 3012), Vector(292, 112));
		OBJECT->CreateProps(OBJ_GROUND, Vector(630, 3091), Vector(184, 46));
		OBJECT->CreateProps(OBJ_GROUND, Vector(311, 892), Vector(-50, -104));
		OBJECT->CreateProps(OBJ_GROUND, Vector(313, 1354), Vector(-56, -105));
		OBJECT->CreateProps(OBJ_GROUND, Vector(341, 2488), Vector(-47, -102));


		OBJECT->CreateProps(OBJ_HIDE, Vector(880, 658), Vector(-42, -301));
		OBJECT->CreateProps(OBJ_HIDE, Vector(628, 2119), Vector(-133, -117));
		OBJECT->CreateProps(OBJ_HIDE, Vector(623, 2115), Vector(-64, -57));




		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, 800, 600);
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
			if (MATH->IsCollided(m_cursor, Vector(634, 10), Vector(690, 63))) //포션
			{

				CurrentHp += UI->EatPotion();
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
		//if (INPUT->IsKeyPress(VK_LEFT)) CurrentHp -= 8;
		//if (INPUT->IsKeyPress(VK_RIGHT)) CurrentHp += 8;





	}

	void OnExit()
	{
		/*SOUND->Stop("IntroBgm");*/
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_DungeonBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		UI->Draw(MaxHp, CurrentHp);
		UI->DrawSetting();
		pMainCamera->Draw(m_DungeonBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}
};
