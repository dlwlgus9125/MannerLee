#include "GameManager.h"

HINSTANCE g_hInst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	g_hInst = hInstance;

	GAME->Init();

	// �޽��� ����//test
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);		// �޽��� ����
			DispatchMessage(&msg);		// �޽��� ó�� �Լ� ȣ��
		}

		GAME->Update();
	}

	GAME->Release();

	return (int)msg.wParam;
}