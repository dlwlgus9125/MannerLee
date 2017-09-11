#include "GameManager.h"


void GameManager::Init()
{
	m_frameTime = 1.0f / (float)FPS;
	m_currentTime = timeGetTime();
	m_prevTime = timeGetTime();
	WINDOW->RegisterData(TEXT("Main"), CS_HREDRAW | CS_VREDRAW, RGB(255, 255, 255), WndProc);
	WINDOW->Create(WND_MAIN, TEXT("Main"), TEXT("MainWindow"), 0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	

	INPUT->Init(WINDOW->GetHandle(WND_MAIN));
	SOUND->Init();
	RENDER->Init(WINDOW->GetHandle(WND_MAIN));
	SCENE->Register(SCENE_TITLE, new TitleScene());
	SCENE->Register(SCENE_DUNGEON, new DungeonScene());
	SCENE->Register(SCENE_FEILD, new FieldScene());
	SCENE->Register(SCENE_TEST, new TestScene());
	SCENE->Register(SCENE_DEATH, new DeadScene());
	SCENE->ChangeScene(SCENE_DUNGEON);

	RENDER->LoadImageFiles(TEXT("Danger"), TEXT("Image/Danger"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Fire_Bolt"), TEXT("Image/Magic/Fire/Bolt/Bolt"), TEXT("png"), 11);
	RENDER->LoadImageFiles(TEXT("Fire_Shield"), TEXT("Image/Magic/Fire/Barrier/Barrier_"), TEXT("png"), 8);
	RENDER->LoadImageFiles(TEXT("Fire_Wall"), TEXT("Image/Magic/Fire/Wall/Wall_"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Fire_Explosion"), TEXT("Image/Magic/Fire/Explosion/Explosion_Fire_"), TEXT("png"), 23);
	RENDER->LoadImageFiles(TEXT("Ice_Bolt"), TEXT("Image/Magic/Water/Bolt/Bolt_"), TEXT("png"), 7);
	RENDER->LoadImageFiles(TEXT("Ice_Shield"), TEXT("Image/Magic/Water/Barrier/Barrier_"), TEXT("png"), 8);
	RENDER->LoadImageFiles(TEXT("Ice_Wall"), TEXT("Image/Magic/Water/Wall/Wall_"), TEXT("png"), 30);
	RENDER->LoadImageFiles(TEXT("Ice_Explosion"), TEXT("Image/Magic/Water/Explosion/Explosion_"), TEXT("png"), 11);
	RENDER->LoadImageFiles(TEXT("Electricity_Bolt"), TEXT("Image/Magic/Electricity/Bolt/Bolt_"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Electricity_Shield"), TEXT("Image/Magic/Electricity/Barrier/Barrier_"), TEXT("png"), 8);
	RENDER->LoadImageFiles(TEXT("Electricity_Wall"), TEXT("Image/Magic/Electricity/Wall/Wall_"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Electricity_Explosion"), TEXT("Image/Magic/Electricity/Explosion/Explosion_Electricity_"), TEXT("png"), 6);



	RENDER->LoadImageFiles(TEXT("Attribute_Water"), TEXT("Image/Magic/Circle/Blue/Circle_Blue_"), TEXT("png"), 8);
	SOUND->LoadFile("Explosion_Fire", "Sound/Effect/Explosion_Fire.wav", false);
	SOUND->LoadFile("Explosion_Water", "Sound/Effect/Explosion_Water.wav", false);
	SOUND->LoadFile("Explosion_Electricity", "Sound/Effect/Explosion_Electricity.wav", false);
	SOUND->LoadFile("Wall_Fire", "Sound/Effect/Wall_Fire.wav", false);
	SOUND->LoadFile("Wall_Water", "Sound/Effect/Wall_Water.wav", false);
	SOUND->LoadFile("Wall_Electricity", "Sound/Effect/Wall_Electricity.wav", false);
	SOUND->LoadFile("Shield_Fire", "Sound/Effect/Shield_Fire.wav", false);
	SOUND->LoadFile("Shield_Water", "Sound/Effect/Shield_Water.wav", false);
	SOUND->LoadFile("Shield_Electricity", "Sound/Effect/Shield_Electricity.mp3", false);
	SOUND->LoadFile("Wall_Fire", "Sound/Effect/Wall_Fire.wav", false);
	SOUND->LoadFile("Wall_Water", "Sound/Effect/Wall_Water.wav", false);
	SOUND->LoadFile("Wall_Electricity", "Sound/Effect/Wall_Electricity.mp3", false);
	SOUND->LoadFile("Hit", "Sound/Effect/Hit.wav", false);
	SOUND->LoadFile("BossHit", "Sound/Effect/BossHit.wav", false);
	SOUND->LoadFile("MonsterHit", "Sound/Effect/MonsterHit.wav", false);
	SOUND->LoadFile("FireBoltShot", "Sound/Effect/FireBoltShot.mp3", false);
	SOUND->LoadFile("WaterBoltShot", "Sound/Effect/WaterBoltShot.mp3", false);
	SOUND->LoadFile("ElectBoltShot", "Sound/Effect/ElectBoltShot.mp3", false);
	SOUND->LoadFile("Stair", "Sound/Effect/Stair.wav", false);
	SOUND->LoadFile("PotionSound", "Sound/Effect/PotionSound.wav", false);
	
	
	SOUND->LoadFile("BossBgm", "Sound/Boss2.wav", true);
	SOUND->LoadFile("WarBgm", "Sound/WarBgm.wav", true);
	SOUND->LoadFile("PotionEffect", "Sound/Effect/PotionSound.wav", false);
	SOUND->LoadFile("BossVoice", "Sound/Effect/BossVoice.wav", false);
}

void GameManager::Release()
{
	RENDER->Release();
	SOUND->Release();
	INPUT->Release();
	WINDOW->Destroy(WND_MAIN);
}

void GameManager::Update()
{
	m_currentTime = timeGetTime();
	float deltaTime = (m_currentTime - m_prevTime) * 0.001f;	// 실제 한 프레임 시간
	

	if (deltaTime >= m_frameTime)
	{
		cout << deltaTime << endl;
		m_prevTime = m_currentTime;
		SOUND->Update(deltaTime);
		INPUT->Update();
		SCENE->Update(deltaTime);
		OBJECT->DestroyCompletedSkill();

		InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
	}
}

void GameManager::Render(HDC hdc)
{
	
	
	SCENE->Draw();
	RENDER->Render(hdc);
}



