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
	SCENE_NONE, SCENE_FEILD, SCENE_DUNGEON, SCENE_TEST,SCENE_TITLE, SCENE_DEAD
};

enum CHARACTER_STATE
{
	CHARACTER_NONE, CHARACTER_IDLE, CHARACTER_RUN,  
	CHARACTER_HIT, CHARACTER_CAST_ATTRIBUTE, CHARACTER_CAST_TYPE, CHARACTER_CAST_END, CHARACTER_DEATH, 
};

enum SPRITE_STATE
{
	SPRITE_NONE,
	IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT,
	RUN_UP, RUN_DOWN, RUN_LEFT, RUN_RIGHT,
	ATTACK_UP=5000, ATTACK_DOWN, ATTACK_LEFT, ATTACK_RIGHT,

	MINION_IDLE_UP, MINION_IDLE_DOWN, MINION_IDLE_LEFT, MINION_IDLE_RIGHT,
	MINION_RUN_UP, MINION_RUN_DOWN, MINION_RUN_LEFT, MINION_RUN_RIGHT,
	MINION_ATTACK_UP, MINION_ATTACK_DOWN, MINION_ATTACK_LEFT, MINION_ATTACK_RIGHT,
	BOSS_IDLE=6000, BOSS_ATTACK, BOSS_DEATH,
};



enum DIR_STATE
{
	DIR_NONE,
	DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT,
};

enum MONSTER_KIND
{
	MONSTER_MINION_RED=1000, MONSTER_MINION_BLUE=2000,MONSTER_MINION_YELLOW =3000, MONSTER_BOSS,
};

enum EYE_STATE
{
	EYE_GREEN=10000, EYE_RED, EYE_BLUE, EYE_YELLOW,
};

enum OBJ_TAG
{
	OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER,
	OBJ_WALL, OBJ_GROUND, OBJ_GATE, OBJ_SKILL, OBJ_HIDE, OBJ_BOSS,
	OBJ_DEAD,
};

enum SKILL_ATTRIBUTE
{
	ATTRIBUTE_NONE,ATTRIBUTE_FIRE=10,ATTRIBUTE_WATER=20,ATTRIBUTE_ELECTRICITY=30,
};

enum SKILL_TYPE
{
	TYPE_NONE,TYPE_BOLT, TYPE_SHIELD,TYPE_WALL,
};

enum RUNE_STATE
{
	RUNE_NONE, RUNE_FIRE=40, RUNE_ICE, RUNE_ELECTRICITY, RUNE_BOLT, RUNE_SHIELD, RUNE_WALL,
};

enum CORRECT_STATE
{
	CORRECT_NONE, CORRECT_FIRE=46, CORRECT_ICE, CORRECT_ELECTRICITY, CORRECT_BOLT, CORRECT_SHIELD, CORRECT_WALL,

};

enum SKILL_LIST
{
	SKILL_NONE,
	FIRE_BOLT=11,FIRE_SHIELD=12, FIRE_WALL = 13, FIRE_EXPLOSION,
	WATER_BOLT=21,WATER_SHIELD=22, WATER_WALL=23, WATER_EXPLOSION,
	ELECTRICITY_BOLT=31,ELECTRICITY_SHIELD=32, ELECTRICITY_WALL=33, ELECTRICITY_EXPLOSION,
};


enum SKILL_STATE
{
	STATE_ATTRIBUTE ,STATE_TYPE, STATE_BOLT,STATE_WALL,STATE_SHIELD, MONSTER_ATTACK, STATE_START, STATE_IDLE,STATE_VANISH, STATE_EXPLOSION
};

enum SKILL_USER
{
	USER_PLAYER, USER_MINION,
};

class Magic
{
	SKILL_LIST m_name;

	float m_damage;
	float m_speed;
	float m_time;
	float m_life;

	SKILL_TYPE m_type;
	SKILL_ATTRIBUTE m_attribute;



public:
	Magic(SKILL_LIST name)
	{
		m_name = name;
		SetSkillStatus(name);
	}

	void SetSkillStatus(SKILL_LIST name)
	{
		switch (name)
		{
		case FIRE_BOLT:			SetSkillStatus(0.001f, 100, 3, 1, ATTRIBUTE_FIRE, TYPE_BOLT);					break;
		case FIRE_WALL:			SetSkillStatus(0.001f, 0, 4, 1000, ATTRIBUTE_FIRE, TYPE_WALL);				break;
		case FIRE_SHIELD:		SetSkillStatus(0.001f, 0, 5, 500, ATTRIBUTE_FIRE, TYPE_SHIELD);				break;
		case WATER_BOLT:		SetSkillStatus(0.001f, 100, 3, 1, ATTRIBUTE_WATER, TYPE_BOLT);				break;
		case WATER_WALL:		SetSkillStatus(0.001f, 0, 4, 1000, ATTRIBUTE_WATER, TYPE_WALL);				break;
		case WATER_SHIELD:		SetSkillStatus(0.001f, 0, 5, 500, ATTRIBUTE_WATER, TYPE_SHIELD);				break;
		case ELECTRICITY_BOLT:	SetSkillStatus(0.001f, 100, 3, 1, ATTRIBUTE_ELECTRICITY, TYPE_BOLT);			break;
		case ELECTRICITY_WALL:	SetSkillStatus(0.001f, 0, 4, 1000, ATTRIBUTE_ELECTRICITY, TYPE_WALL);		break;
		case ELECTRICITY_SHIELD:SetSkillStatus(0.001f, 0, 5, 500, ATTRIBUTE_ELECTRICITY, TYPE_SHIELD);			break;
		}
	}
	
	void SetSkillStatus(float damage,float speed,float time,float life,SKILL_ATTRIBUTE attribute,SKILL_TYPE type)
	{
		this->m_damage = damage;
		this->m_speed = speed;
		this->m_time = time;
		this->m_life = life;
		this->m_attribute = attribute;
		this->m_type = type;
	}

	SKILL_LIST GetSkillName() { return m_name; }
	SKILL_ATTRIBUTE GetAttribute() { return m_attribute; }
	SKILL_TYPE GetSkillType() { return m_type; }

	float GetDamage() { return m_damage; }
	float GetSpeed() { return m_speed; }
	float GetTime() { return m_time; }
	float GetLife() { return m_life; }

	void SetDamage(float damage) { m_damage = damage; }
	void SetLife(float life) { m_life += life; }
	void SetTIme(float time) { m_time = time; }
	void SetTimer(float time) { m_time += time; }
};