#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Common.h"


class DeadScene : public IScene
{
	AnimationController* m_pBg;

public:

	DeadScene()
	{
		RENDER->LoadImageFiles(TEXT("DeadBg"), TEXT("Image/DeadScene/Dead_"), TEXT("png"), 2);
		m_pBg = new AnimationController();
		m_pBg->Register(OBJ_DEAD,
			new Animation(TEXT("DeadBg"), 2, 3, true));
	}

	void OnEnter()
	{
		if (SOUND->FindChannel("Death") == NULL)SOUND->Play("Death", 2.0f);
	}

	void OnUpdate(float deltaTime)
	{

		m_pBg->Update(deltaTime);
		
		if (INPUT->IsKeyUp(VK_RETURN))
		{
			PostQuitMessage(0);
		}

	}

	void OnExit()
	{
		delete m_pBg;
	}

	void OnDraw()
	{
		RENDER->Draw(m_pBg->Current()->GetSprite(), 400, 300);
	}


};