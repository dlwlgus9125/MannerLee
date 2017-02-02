#pragma once
#include "Common.h"
#include "WinManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "GameMain.h"

#define GAME GameManager::Instance()

class GameManager : public Singleton<GameManager>
{
	float m_frameTime;			// 한 프레임당 시간
	float m_currentTime;		// 현재 프레임의 시간
	float m_prevTime;			// 이전 프레임의 시간

public:
	void Init();

	void Release();

	void Update();

	void Render(HDC hdc);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
