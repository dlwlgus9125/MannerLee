#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Common.h"



class FieldScene : public IScene
{
	Sprite* m_pBg;
	Sprite* m_UI;


	Vector SkillSize;
public:
	FieldScene()
	{
		RENDER->CreateCamera(CAM_MAIN, 860 * 2.0f, 1100 * 2.0f, VIEW_WIDTH, VIEW_HEIGHT);
		//RENDER->CreateCamera(CAM_MAP, 2000, 3000, 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));
		RENDER->LoadImageFile(TEXT("UI"), TEXT("Image/UI/UI.png"));

		

		OBJECT->CreatePlayer(Vector(600, 800), 30);
		OBJECT->CreateSkill(OBJECT->GetPlayer(), SKILL_NONE, SkillSize);

		OBJECT->CreateMonster(OBJ_MONSTER, MONSTER_MINION_RED, Vector(600, 600), 30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 1.0f, 0, 0));
		m_pBg->SetSize(860 * 2.0f, 1100 * 2.0f);
		NEW_OBJECT(m_UI, Sprite(RENDER->GetImage(TEXT("UI")), 1.0f, 0, 0));

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
		OBJECT->Update(deltaTime);
		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(OBJECT->GetPlayer()->Position());
	
		if (INPUT->IsKeyDown(VK_TAB))RENDER->GetCamera(CAM_MAIN)->SetIsWaveTrue();
		if (RENDER->GetCamera(CAM_MAIN)->GetIsWave())
		{
			RENDER->GetCamera(CAM_MAIN)->ShakingCamera(5);
		}





	}

	void OnExit()
	{
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_UI);
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		pMainCamera->Draw(m_pBg, Vector(0, 0));
		RENDER->Draw(m_UI, 0, 0);
		OBJECT->Draw(pMainCamera);
	}
};