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
	CAM_NONE, CAM_MAIN, CAM_UI, CAM_MAP, CAM_DUNGEON, CAM_TEST
};

enum SCENE_TAG
{
	SCENE_NONE, SCENE_FEILD, SCENE_DUNGEON, SCENE_TEST
};

enum CHARACTER_STATE
{
	CHARACTER_NONE, CHARACTER_IDLE, CHARACTER_RUN,  
	CHARACTER_HIT, CHARACTER_CAST_ATTRIBUTE, CHARACTER_CAST_TYPE, CHARACTER_CAST_END,
};

enum SPRITE_STATE
{
	SPRITE_NONE,
	IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT,
	RUN_UP, RUN_DOWN, RUN_LEFT, RUN_RIGHT,
	ATTACK_UP, ATTACK_DOWN, ATTACK_LEFT, ATTACK_RIGHT,

	MINION_IDLE_UP, MINION_IDLE_DOWN, MINION_IDLE_LEFT, MINION_IDLE_RIGHT,
	MINION_RUN_UP, MINION_RUN_DOWN, MINION_RUN_LEFT, MINION_RUN_RIGHT,
	MINION_ATTACK_UP, MINION_ATTACK_DOWN, MINION_ATTACK_LEFT, MINION_ATTACK_RIGHT,
};

enum DIR_STATE
{
	DIR_NONE,
	DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT,
};

enum MONSTER_KIND
{
	MONSTER_MINION_RED, MONSTER_BOSS,
};

enum OBJ_TAG
{
	OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER,
	OBJ_WALL, OBJ_GROUND, OBJ_GATE, OBJ_SKILL, OBJ_HIDE,
};

enum SKILL_ATTRIBUTE
{
	ATTRIBUTE_NONE,ATTRIBUTE_FIRE=10,ATTRIBUTE_WATER=20,ATTRIBUTE_ELECTRICITY=30,
};

enum SKILL_TYPE
{
	TYPE_NONE,TYPE_BOLT, TYPE_SHIELD,TYPE_WALL,
};
enum SKILL_LIST
{
	SKILL_NONE,
	FIRE_BOLT=11,FIRE_SHIELD=12, FIRE_WALL = 13,
	WATER_BOLT=21,WATER_SHIELD=22, WATER_WALL=23,
	ELECTRICITY_BOLT=31,ELECTRICITY_SHIELD=32, ELECTRICITY_WALL=33,
};


enum SKILL_STATE
{
	STATE_ATTRIBUTE ,STATE_TYPE, STATE_BOLT,STATE_WALL,STATE_SHIELD, MONSTER_ATTACK, STATE_START, STATE_IDLE,
};

enum SKILL_USER
{
	USER_PLAYER, USER_MINION,
};