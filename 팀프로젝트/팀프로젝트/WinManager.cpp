#include "WinManager.h"



void WindowManager::RegisterData(TCHAR* dataName, UINT style, COLORREF bgColor, WNDPROC wndProc)
{
	WNDCLASS* pWndClass = new WNDCLASS;
	pWndClass->cbClsExtra = 0;		// Ư�� ������ ���� ���� ����
	pWndClass->cbWndExtra = 0;		// Ư�� ������ ���� ���� ����
	pWndClass->hbrBackground = CreateSolidBrush(bgColor);	// ��׶��� �귯�� ����
	pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);		// Ŀ�� ����
	pWndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ����
	pWndClass->hInstance = g_hInst;						// �ν��Ͻ� ����
	pWndClass->lpfnWndProc = wndProc;						// �޽��� ó�� �Լ� ����
	pWndClass->lpszClassName = dataName;					// ������ �̸� ����
	pWndClass->lpszMenuName = NULL;						// �޴� ���� (�޴��� ���� ������� NULL)
	pWndClass->style = style;			// �������� ���μ��� ũ�Ⱑ ���ҽÿ� �ٽ� �׸���.

	RegisterClass(pWndClass);
}

Window* WindowManager::Get(int windowID)
{
	if (m_windows.find(windowID) != m_windows.end())
	{
		return m_windows[windowID];
	}
	return NULL;
}

HWND WindowManager::GetHandle(int windowID)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		return pWindow->handle;
	}
	return NULL;
}

void WindowManager::Create(int windowID, TCHAR* dataName, TCHAR* title, int x, int y, int width, int height)
{
	DWORD style = WS_CAPTION | WS_SYSMENU;
	HWND hWnd = CreateWindow(dataName, title, style, x, y, width, height, NULL, NULL, g_hInst, NULL);
	ShowWindow(hWnd, SW_SHOW);

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, style, false);
	MoveWindow(hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);

	m_windows[windowID] = new Window(hWnd, x, y, width, height);
}

LRESULT WindowManager::Send(int windowID, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		return SendMessage(pWindow->handle, msg, wParam, lParam);
	}
	return -1;
}

void WindowManager::Destroy(int windowID)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		m_windows.erase(windowID);
		delete pWindow;
	}
}