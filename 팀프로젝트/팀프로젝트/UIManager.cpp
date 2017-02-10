#include "UIManager.h"
#include "Player.h"



UIManager::UIManager()
{
	m_NotRun = false;
	RENDER->LoadImageFile(TEXT("UI"), TEXT("Image/UI/UI.png"));
	RENDER->LoadImageFile(TEXT("CT0"), TEXT("Image/UI/CoolTime_0.png"));
	RENDER->LoadImageFile(TEXT("CT1"), TEXT("Image/UI/CoolTime_1.png"));
	RENDER->LoadImageFile(TEXT("HP0"), TEXT("Image/UI/Hp_0.png"));
	RENDER->LoadImageFile(TEXT("HP1"), TEXT("Image/UI/Hp_1.png"));
	NEW_OBJECT(m_UI, Sprite(RENDER->GetImage(TEXT("UI")), 1.0f, 0, 0));
	for (int i = 0; i < HP_CT_LENGTH; i++)
	{
		if (i == 0)
		{
			NEW_OBJECT(m_Hp[i], Sprite(RENDER->GetImage(TEXT("HP0")), 1.0f, 0, 0));
			NEW_OBJECT(m_CoolTime[i], Sprite(RENDER->GetImage(TEXT("CT0")), 1.0f, 0, 0));
		}
		else
		{
			NEW_OBJECT(m_Hp[i], Sprite(RENDER->GetImage(TEXT("HP1")), 1.0f, 0, 0));
			NEW_OBJECT(m_CoolTime[i], Sprite(RENDER->GetImage(TEXT("CT1")), 1.0f, 0, 0));
		}
	}
}


UIManager::~UIManager()
{
	DELETE_OBJECT(m_UI);
	for (int i = 0; i < HP_CT_LENGTH; i++)
	{
		DELETE_OBJECT(m_Hp[i]);
		DELETE_OBJECT(m_CoolTime[i]);
	}
}

void UIManager::Draw(float MaxHp, float& CurrentHP)
{
	float percent_Hp = MaxHp / (float)HP_CT_LENGTH;

	CurrentHP = MATH->Clamp(CurrentHP, 0.0f, MaxHp);

	RENDER->Draw(m_UI, 0, 0);
	for (int i = 0; i < ((int)(CurrentHP / percent_Hp)); i++)
	{
		RENDER->Draw(m_Hp[i], 94+i, 10);
	}

	for (int i = 0; i < HP_CT_LENGTH; i++)
	{
		RENDER->Draw(m_CoolTime[i], 94 + i, 34);
	}//test
}