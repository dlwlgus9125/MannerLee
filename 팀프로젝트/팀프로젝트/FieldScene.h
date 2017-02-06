#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "Common.h"



class FieldScene : public IScene
{
	Sprite* m_pBg;

public:
	FieldScene()
	{
		RENDER->CreateCamera(CAM_MAIN,Vector(3000, 1000), VIEW_WIDTH, VIEW_HEIGHT);
		RENDER->CreateCamera(CAM_MAP,Vector(3000, 1000), 3000, 1000);

		RENDER->LoadImageFile(TEXT("BossCastle"), TEXT("Image/Boss.png"));


	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("BossCastle")), 1.0f, 0, 0));
		m_pBg->SetSize(3000, 1000);

		RENDER->GetCamera(CAM_MAIN)->SetScreenRect(100, 100, 600, 400);
		RENDER->GetCamera(CAM_MAP)->SetScreenRect(0, 0, 200, 200);

		}

	void OnUpdate(float deltaTime)
	{
		//OBJECT->Update(deltaTime);
		RENDER->GetCamera(CAM_MAIN)->SetCenterPos(MAIN->getTest().getVector());

		
	}

	void OnExit()
	{
		
		DELETE_OBJECT(m_pBg);
	}

	void OnDraw()
	{
		Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
		Camera* pMapCamera = RENDER->GetCamera(CAM_MAP);
		pMapCamera->Draw(m_pBg, Vector(0, 0));

		pMainCamera->Draw(m_pBg, Vector(0, 0));
		
	}
};