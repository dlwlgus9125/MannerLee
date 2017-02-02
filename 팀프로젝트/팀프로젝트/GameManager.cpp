#include "GameManager.h"

void GameManager::Init()
{
	m_frameTime = 1.0f / (float)FPS;
	m_currentTime = (float)timeGetTime() * 0.001f;
	m_prevTime = (float)timeGetTime() * 0.001f;

	WINDOW->RegisterData(TEXT("Main"), CS_HREDRAW | CS_VREDRAW, RGB(255, 255, 255), WndProc);
	WINDOW->Create(WND_MAIN, TEXT("Main"), TEXT("MainWindow"), 0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	INPUT->Init(WINDOW->GetHandle(WND_MAIN));
	RENDER->Init(WINDOW->GetHandle(WND_MAIN));
	MAIN->Init();
}

void GameManager::Release()
{
	MAIN->Release();
	RENDER->Release();
	INPUT->Release();
	WINDOW->Destroy(WND_MAIN);
}

void GameManager::Update()
{
	m_currentTime = (float)timeGetTime() * 0.001f;
	float deltaTime = m_currentTime - m_prevTime;	// 실제 한 프레임 시간

	if (deltaTime >= m_frameTime)
	{
		m_prevTime = m_currentTime;
		INPUT->Update();
		MAIN->Update(deltaTime);

		InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
	}
}

void GameManager::Render(HDC hdc)
{
	MAIN->Render();
	RENDER->Render();
}

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