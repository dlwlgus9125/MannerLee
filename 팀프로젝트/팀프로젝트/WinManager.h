#pragma once
#include "Common.h"

#define WINDOW	WindowManager::Instance()

extern HINSTANCE g_hInst;

struct Window
{
	HWND handle;
	int x, y;
	int width, height;

	Window(HWND hWnd, int x, int y, int width, int height)
	{
		this->handle = hWnd;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

class WindowManager : public Singleton<WindowManager>
{
	map<int, Window*> m_windows;

public:
	void RegisterData(TCHAR* dataName, UINT style, COLORREF bgColor, WNDPROC wndProc);

	Window* Get(int windowID);

	HWND GetHandle(int windowID);

	void Create(int windowID, TCHAR* dataName, TCHAR* title, int x, int y, int width, int height);

	LRESULT Send(int windowID, UINT msg, WPARAM wParam, LPARAM lParam);

	void Destroy(int windowID);
};

