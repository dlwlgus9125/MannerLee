#pragma once
#include "Common.h"

#define MAIN	GameMain::Instance()


class GameMain : public Singleton<GameMain>
{
	
	//test
public:
	void Init();

	void Release();

	void Update(float deltaTime);

	void Render();
};