#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Common.h"



class FieldScene : public IScene
{
	Sprite* m_pBg;
	Sprite* m_UI;

public:
	FieldScene()
	{
		RENDER->CreateCamera(CAM_MAIN, 860*1.5f, 1100* 1.5f, VIEW_WIDTH, VIEW_HEIGHT);
		//RENDER->CreateCamera(CAM_MAP, 2000, 3000, 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));
		RENDER->LoadImageFile(TEXT("UI"), TEXT("Image/UI/UI.png"));


		OBJECT->CreatePlayer(Vector(600, 800), 30);
		OBJECT->CreateMonster(OBJ_MONSTER, Vector(400, 600),30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 1.0f, 0, 0));
		NEW_OBJECT(m_UI, Sprite(RENDER->GetImage(TEXT("UI")), 1.0f, 0, 0));
		m_pBg->SetSize(860* 1.5f, 1100* 1.5f);

		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, 800, 600);
		//RENDER->GetCamera(CAM_MAP)->SetScreenRect(0, 0, 200, 200);

		OBJECT->CreateProps(OBJ_GROUND, Vector(280, 370), Vector(100, 670));
		OBJECT->CreateProps(OBJ_GROUND, Vector(630, 50), Vector(600, 100));
		OBJECT->CreateProps(OBJ_GROUND, Vector(950, 370), Vector(100, 670));
		OBJECT->CreateProps(OBJ_GROUND, Vector(180, 800), Vector(100, 200));
		OBJECT->CreateProps(OBJ_GROUND, Vector(370, 900), Vector(280, 100));
		OBJECT->CreateProps(OBJ_GROUND, Vector(1050, 800), Vector(100, 200));
		OBJECT->CreateProps(OBJ_GROUND, Vector(890, 900), Vector(280, 100));
		//OBJECT->CreateProps(OBJ_GROUND, Vector(300, 1200), Vector(640, 180));
		//OBJECT->CreateProps(OBJ_GROUND, Vector(750, 1150), Vector(190, 230));
		}

	void OnUpdate(float deltaTime)
	{
		OBJECT->Update(deltaTime);
		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(OBJECT->GetPlayer()->Position());

		
	}

	void OnExit()
	{
		OBJECT->DestroyAllProps();
		DELETE_OBJECT(m_pBg);
		DELETE_OBJECT(m_UI);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
	//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		RENDER->Draw(m_UI, 0, 0);
		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}
};