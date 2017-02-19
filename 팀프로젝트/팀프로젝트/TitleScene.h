#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "Common.h"


class TitleScene : public IScene
{
	Sprite* m_pBg;
	Sprite* m_Button;
	Vector m_cursor;// 커서 위치

public:
	TitleScene()
	{
		RENDER->LoadImageFile(TEXT("EIXT"), TEXT("Image/Title/EXIT.png"));
		RENDER->LoadImageFile(TEXT("NOMAL"), TEXT("Image/Title/NOMAL.png"));
		RENDER->LoadImageFile(TEXT("PLAY"), TEXT("Image/Title/PLAY.png"));
		RENDER->LoadImageFile(TEXT("Title"), TEXT("Image/Title/Title.png"));
	}

	void OnEnter()
	{
		NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("Title")), 1.0f, 0, 0));
		NEW_OBJECT(m_Button, Sprite(RENDER->GetImage(TEXT("NOMAL")), 1.0f, 0, 0));
	}

	void OnUpdate(float deltaTime)
	{

		m_cursor = INPUT->GetMousePos();

		NEW_OBJECT(m_Button, Sprite(RENDER->GetImage(TEXT("NOMAL")), 1.0f, 0, 0));

		if (INPUT->IsMousePress(MOUSE_LEFT))
		{
			if (MATH->IsCollided(m_cursor, Vector(465, 245), Vector(714, 316)))
			{
				NEW_OBJECT(m_Button, Sprite(RENDER->GetImage(TEXT("PLAY")), 1.0f, 0, 0));

			
				SCENE->ChangeScene(SCENE_DUNGEON);
			}

			else if (MATH->IsCollided(m_cursor, Vector(465, 355), Vector(714, 427)))
			{
				NEW_OBJECT(m_Button, Sprite(RENDER->GetImage(TEXT("EIXT")), 1.0f, 0, 0));
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
		RENDER->Draw(m_pBg, 0, 0);
		RENDER->Draw(m_Button, 465, 245);
	}


};