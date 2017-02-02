#pragma once
#include "Common.h"

#define MAIN	GameMain::Instance()


class GameMain : public Singleton<GameMain>
{
	

public:
	void Init();

	void Release();

	void Update(float deltaTime);

	void Render();
};