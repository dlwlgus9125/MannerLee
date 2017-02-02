#pragma once
#pragma comment(lib, "winmm.lib")
#include "Common.h"
#include "WinManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "GameMain.h"
#include "SceneManager.h"
#include "FieldScene.h"

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

	static LRESULT CALLBACK GameManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			GAME->Render(hdc);

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0;
	}
};
