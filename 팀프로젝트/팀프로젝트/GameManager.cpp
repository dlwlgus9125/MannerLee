#include "GameManager.h"

void GameManager::Init()
{
	m_frameTime = 1.0f / (float)FPS;
	m_currentTime = timeGetTime();
	m_prevTime = timeGetTime();

	WINDOW->RegisterData(TEXT("Main"), CS_HREDRAW | CS_VREDRAW, RGB(255, 255, 255), WndProc);
	WINDOW->Create(WND_MAIN, TEXT("Main"), TEXT("MainWindow"), 0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	INPUT->Init(WINDOW->GetHandle(WND_MAIN));
	//SOUND->Init();
	RENDER->Init(WINDOW->GetHandle(WND_MAIN));
	SCENE->Register(SCENE_DUNGEON, new DungeonScene());
	SCENE->Register(SCENE_FEILD, new FieldScene());
	SCENE->Register(SCENE_TEST, new TestScene());
	SCENE->ChangeScene(SCENE_TEST);
}

void GameManager::Release()
{
	RENDER->Release();
	//SOUND->Release();
	INPUT->Release();
	WINDOW->Destroy(WND_MAIN);
}

void GameManager::Update()
{
	m_currentTime = timeGetTime();
	float deltaTime = (m_currentTime - m_prevTime) * 0.001f;	// 실제 한 프레임 시간
	
	//cout << "Current: " << m_currentTime << ", Prev: " << m_prevTime << endl;

	if (deltaTime >= m_frameTime)
	{
		m_prevTime = m_currentTime;
		//SOUND->Update(deltaTime);
		INPUT->Update();
		SCENE->Update(deltaTime);
		OBJECT->DestroyCompletedSkill();

		InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
	}
}

void GameManager::Render(HDC hdc)
{
	
	RENDER->Render(hdc);
	SCENE->Draw();
	
}

