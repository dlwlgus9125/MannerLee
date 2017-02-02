#pragma once
#include "Common.h"
#include "WinManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "GameMain.h"

#define GAME GameManager::Instance()

class GameManager : public Singleton<GameManager>
{
	float m_frameTime;			// �� �����Ӵ� �ð�
	float m_currentTime;		// ���� �������� �ð�
	float m_prevTime;			// ���� �������� �ð�

public:
	void Init();

	void Release();

	void Update();

	void Render(HDC hdc);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
