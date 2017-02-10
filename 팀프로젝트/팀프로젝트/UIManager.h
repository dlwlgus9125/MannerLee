#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "Common.h"
#include "Math.h"

#define UI UIManager::Instance()
#define HP_CT_LENGTH 127
#define POTION 200

class UIManager : public Singleton<UIManager>
{

	Sprite* m_UI;
	Sprite* m_Hp[HP_CT_LENGTH];
	Sprite* m_CoolTime[HP_CT_LENGTH];
	bool m_NotRun;

public:
	UIManager();
	~UIManager();

	void Draw(float MaxHp, float& CurrentHP);
	float EatPotion() {	return POTION; }
	bool NotRun() { return m_NotRun; }
	void SetNotRun(bool TF) { m_NotRun = TF; }
};

