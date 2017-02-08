#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Common.h"



class FieldScene : public IScene
{
	Sprite* m_pBg;

public:
	FieldScene()
	{
		RENDER->CreateCamera(CAM_MAIN, 860*1.5f, 1100* 1.5f, VIEW_WIDTH, VIEW_HEIGHT);
		//RENDER->CreateCamera(CAM_MAP, 2000, 3000, 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));

		OBJECT->CreatePlayer(Vector(600, 800), 30);
		OBJECT->CreateMonster(OBJ_MONSTER, Vector(400, 600),30);
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 1.0f, 0, 0));
		m_pBg->SetSize(860* 1.5f, 1100* 1.5f);

		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, 800, 600);
		//RENDER->GetCamera(CAM_MAP)->SetScreenRect(0, 0, 200, 200);

		OBJECT->CreateProps(OBJ_GROUND, Vector(200, 100), Vector(100, 710));
		//OBJECT->CreateProps(OBJ_GROUND, Vector(250, 710), Vector(740, 130));
		//OBJECT->CreateProps(OBJ_GROUND, Vector(560, 820), Vector(120, 400));
		//->CreateProps(OBJ_GROUND, Vector(300, 1150), Vector(190, 230));
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
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	//	Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
	//	pMapCamera->Draw(m_pBg, Vector(0, 0));

		pMainCamera->Draw(m_pBg, Vector(0, 0));
		OBJECT->Draw(pMainCamera);
	}
};