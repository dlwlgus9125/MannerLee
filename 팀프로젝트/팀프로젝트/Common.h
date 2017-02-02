#pragma once
#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <list>
#include <map>
#include <queue>
#include "Singleton.h"
#include "Math.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

#define DpELETE_OBJECT()	if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p)	if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define RELEASE_OBJECT(p)	if ((p) != NULL) { (p)->Release(); (p) = NULL; }
#define FOR_LIST(type, li)	for (list<type>::iterator it = li.begin(); it != li.end(); it++)

#define FPS				60
#define VIEW_WIDTH		800
#define VIEW_HEIGHT		600

enum WND_TAG
{
	WND_NONE, WND_MAIN,
};