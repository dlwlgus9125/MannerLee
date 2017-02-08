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

#define NEW_OBJECT(p, type) p = new type
#define DELETE_OBJECT(p) if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p) if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define RELEASE_OBJECT(p)	if ((p) != NULL) { (p)->Release(); (p) = NULL; }


#define DpELETE_OBJECT()	if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p)	if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define FOR_LIST(type, li)	for (list<type>::iterator it = li.begin(); it != li.end(); it++)

#define FPS				60
#define VIEW_WIDTH		800
#define VIEW_HEIGHT		600

enum WND_TAG
{
	WND_NONE, WND_MAIN,
};

enum CAMERA_TAG
{
	CAM_NONE, CAM_MAIN, CAM_UI, CAM_MAP,
};

enum SCENE_TAG
{
	SCENE_NONE, SCENE_FEILD,
};

enum CHARACTER_STATE
{
	CHARACTER_NONE, CHARACTER_IDLE, CHARACTER_RUN, CHARACTER_ATTACK,
	CHARACTER_HIT,
};

enum MONSTER_KIND
{
	MONSTER_MINION_RED, MONSTER_BOSS,
};

enum OBJ_TAG
{
	OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER,
	OBJ_WALL, OBJ_GROUND, OBJ_GATE,
};