#include "UIManager.h"
#include "Player.h"



UIManager::UIManager()
{
	m_NotRun = false;
	m_Setting = MOUSE;
	m_SettingDraw = false;
	RENDER->LoadImageFile(TEXT("UI"), TEXT("Image/UI/UI.png"));
	RENDER->LoadImageFile(TEXT("CT0"), TEXT("Image/UI/CoolTime_0.png"));
	RENDER->LoadImageFile(TEXT("CT1"), TEXT("Image/UI/CoolTime_1.png"));
	RENDER->LoadImageFile(TEXT("HP0"), TEXT("Image/UI/Hp_0.png"));
	RENDER->LoadImageFile(TEXT("HP1"), TEXT("Image/UI/Hp_1.png"));
	RENDER->LoadImageFile(TEXT("MOUSE"), TEXT("Image/UI/Setting_0.png"));
	RENDER->LoadImageFile(TEXT("KEYBOARD"), TEXT("Image/UI/Setting_1.png"));
	RENDER->LoadImageFile(TEXT("SETTINGBG"), TEXT("Image/UI/Setting.png"));
	NEW_OBJECT(m_UI, Sprite(RENDER->GetImage(TEXT("UI")), 1.0f, 0, 0));
	NEW_OBJECT(m_Setting_0, Sprite(RENDER->GetImage(TEXT("MOUSE")), 1.0f, 0, 0));
	NEW_OBJECT(m_Setting_1, Sprite(RENDER->GetImage(TEXT("KEYBOARD")), 1.0f, 0, 0));
	NEW_OBJECT(m_SettingBG, Sprite(RENDER->GetImage(TEXT("SETTINGBG")), 1.0f, 0, 0));
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
	DELETE_OBJECT(m_SettingBG);
	DELETE_OBJECT(m_Setting_0);
	DELETE_OBJECT(m_Setting_1);
	for (int i = 0; i < HP_CT_LENGTH; i++)
	{
		DELETE_OBJECT(m_Hp[i]);
		DELETE_OBJECT(m_CoolTime[i]);
	}
}

void UIManager::Draw(float MaxHp, float CurrentHP)
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

void UIManager::DrawSetting()
{
	if (m_SettingDraw)
	{
		RENDER->Draw(m_SettingBG, 250, 59);
		if (m_Setting == KEYBOARD)
		{
			RENDER->Draw(m_Setting_1, 298, 186);
		}

		if (m_Setting == MOUSE)
		{
			RENDER->Draw(m_Setting_0, 298, 186);
		}
	}
}