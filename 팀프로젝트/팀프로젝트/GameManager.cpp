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
	SCENE->Register(SCENE_FEILD, new FieldScene());
	SCENE->ChangeScene(SCENE_FEILD);
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
		SCENE->Update(deltaTime);
		MAIN->Update(deltaTime);

		InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
	}
}

void GameManager::Render(HDC hdc)
{
	
	RENDER->Render(hdc);
	SCENE->Draw();
	MAIN->Render();
}

