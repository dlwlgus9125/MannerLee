#pragma once
#include "Common.h"
#include "InputManager.h"
#include "RenderManager.h"

#define MAIN	GameMain::Instance()

class Test
{
	Vector m_point;

public:
	Test()
	{
		m_point = Vector(400, 400);
	}

	Vector getVector() { return m_point; }

	void Update(float deltaTime)
	{
		if (INPUT->IsKeyPress(VK_LEFT))m_point.x -= 100*deltaTime;
		if (INPUT->IsKeyPress(VK_RIGHT))m_point.x += 100*deltaTime;
		if (INPUT->IsKeyPress(VK_UP))m_point.y -= 100*deltaTime;
		if (INPUT->IsKeyPress(VK_DOWN))m_point.y += 100*deltaTime;
	}

	void Render()
	{
		RENDER->DrawCircle(m_point.x, m_point.y, 30, 30, ColorF::Red, 2);
	}
};

class GameMain : public Singleton<GameMain>
{
	Test test1;
	//test
public:
	void Init();

	void Release();

	void Update(float deltaTime);

	void Render();

	Test getTest() { return test1; }
};