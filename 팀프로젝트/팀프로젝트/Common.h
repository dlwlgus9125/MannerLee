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

enum SKILL_ATTRIBUTE
{
	ATTRIBUTE_NONE,ATTRIBUTE_FIRE,ATTRIBUTE_WATER,ATTRIBUTE_ELECTRICITY,
};

enum SKILL_TYPE
{
	TYPE_NONE,TYPE_BOLT,TYPE_WALL,TYPE_SHIELD,
};
enum SKILL_LIST
{
	SKILL_NONE,
	FIRE_BOLT,FIRE_WALL,FIRE_SHIELD,
	WATER_BOLT,WATER_WALL,WATER_SHIELD,
	ELECTRICITY_BOLT,ELECTRICITY_WALL,ELECTRICITY_SHIELD,
};

enum SKILL_STATE
{
	STATE_ATTRIBUTE ,STATE_TYPE, STATE_BOLT,STATE_WALL,STATE_SHIELD, STATE_STATUS,MONSTER_ATTACK,
};