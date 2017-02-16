#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "Common.h"
#include "Math.h"

#define UI UIManager::Instance()
#define HP_CT_LENGTH 127
#define POTION 200

enum KEYSETTING
{
	KEYBOARD, MOUSE
};

class UIManager : public Singleton<UIManager>
{

	Sprite* m_UI;
	Sprite* m_Hp[HP_CT_LENGTH];
	Sprite* m_CoolTime[HP_CT_LENGTH];
	Sprite* m_SettingBG;
	Sprite* m_Setting_0;
	Sprite* m_Setting_1;
	KEYSETTING m_Setting;

	bool m_SettingDraw;
	bool m_NotRun;

public:
	UIManager();
	~UIManager();

	void Draw(float MaxHp, float CurrentHP);
	float EatPotion() {	return POTION; }
	void DrawSetting();

	bool NotRun() { return m_NotRun; }
	bool SettingDraw() { return m_SettingDraw; }
	void SetSettingDraw(bool TF) { m_SettingDraw = TF; }
	void SetNotRun(bool TF) { m_NotRun = TF; }
	void SetKey(KEYSETTING Key) { m_Setting = Key; }
	KEYSETTING Setting() { return m_Setting; }
};

