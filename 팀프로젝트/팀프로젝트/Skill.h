#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Math.h"
#include "InputManager.h"



class Skill : public Object
{
	SKILL_ATTRIBUTE m_attribute;
	SKILL_TYPE		m_skilltype;

	SKILL_STATE		m_skillState;
	SKILL_LIST		m_skillname;

	Vector			m_pos;
	Vector          m_dir;

	float           m_damage;
	float           m_speed;
	float			m_life;
	float			m_sustainmentTime;

public:
	Skill(Character* pCharacter,SKILL_LIST id) : Object(id)
	{
		m_skillname = id;
		
		m_dir	=	pCharacter->GetDIr();
		m_pos = pCharacter->Position();
	}
	
	void SetSkillStatus(SKILL_LIST id)
	{
		switch (id)
		{
		case SKILL_NONE:
			m_speed = 0;
			m_damage = 0;
			m_life =0;
			m_sustainmentTime =0;
			break;
		case FIRE_BOLT:
			m_speed = 1000;
			m_damage = 300;
			m_life = 1;
			m_sustainmentTime = 1;
			break;
		case FIRE_WALL:
			m_speed =	300;
			m_damage = 300;
			m_life = 900;
			m_sustainmentTime = 5;
			break;
		case FIRE_SHIELD:
			m_speed = 0;
			m_damage = 1;
			m_life = 600;
			m_sustainmentTime = 10;
			break;
		case WATER_BOLT:
			m_speed = 1000;
			m_damage = 300;
			m_life = 1;
			m_sustainmentTime = 1;
			break;
		case WATER_WALL:
			m_speed = 300;
			m_damage = 300;
			m_life = 900;
			m_sustainmentTime = 5;
			break;
		case WATER_SHIELD:
			m_speed = 300;
			m_damage = 300;
			m_life = 600;
			m_sustainmentTime = 10;
			break;
		case ELECTRICITY_BOLT:
			m_speed = 1000;
			m_damage = 300;
			m_life = 1;
			m_sustainmentTime = 1;
			break;
		case ELECTRICITY_WALL:
			m_speed = 300;
			m_damage = 300;
			m_life =	900;
			m_sustainmentTime = 5;
			break;
		case ELECTRICITY_SHIELD:
			m_speed = 0;
			m_damage = 0;
			m_life = 600;
			m_sustainmentTime = 10;
			break;
		}

		m_skillname = id;
	}

	void Update(float deltaTime)
	{
		
	}

	void Draw(Camera* pCamera)
	{
		pCamera->DrawFillCircle(Position(), 30, ColorF::HotPink);
	}

	void AttributeMatch(Skill a,Skill b)
	{
		if (a.m_attribute == ATTRIBUTE_FIRE&&b.m_attribute==ATTRIBUTE_WATER)
		{
			a.SetDamage(0.5);
			b.SetDamage(2);
		}

		if (a.m_attribute == ATTRIBUTE_WATER&&b.m_attribute == ATTRIBUTE_WATER)
		{
			a.SetDamage(1);
			b.SetDamage(1);
		}

		if (a.m_attribute == ATTRIBUTE_ELECTRICITY&&b.m_attribute == ATTRIBUTE_WATER)
		{
			a.SetDamage(2);
			b.SetDamage(0.5);
		}

		if (a.m_attribute == ATTRIBUTE_FIRE&&b.m_attribute == ATTRIBUTE_FIRE)
		{
			a.SetDamage(1);
			b.SetDamage(1);
		}

		if (a.m_attribute == ATTRIBUTE_WATER&&b.m_attribute == ATTRIBUTE_FIRE)
		{
			a.SetDamage(2);
			b.SetDamage(0.5);
		}

		if (a.m_attribute == ATTRIBUTE_ELECTRICITY&&b.m_attribute == ATTRIBUTE_FIRE)
		{
			a.SetDamage(0.5);
			b.SetDamage(2);
		}

		if (a.m_attribute == ATTRIBUTE_FIRE&&b.m_attribute == ATTRIBUTE_ELECTRICITY)
		{
			a.SetDamage(2);
			b.SetDamage(0.5);
		}

		if (a.m_attribute == ATTRIBUTE_WATER&&b.m_attribute == ATTRIBUTE_ELECTRICITY)
		{
			a.SetDamage(0.5);
			b.SetDamage(2);
		}
		if (a.m_attribute == ATTRIBUTE_ELECTRICITY&&b.m_attribute == ATTRIBUTE_ELECTRICITY)
		{
			a.SetDamage(1);
			b.SetDamage(1);
		}
	}
	
	void SetDamage(float damage) {	m_damage *= damage; }
	void SetLife(float damage) {	m_life-=damage;}
	void SetsustainmentTime(float time) { m_sustainmentTime *= time; }
	float GetDamage() { return m_damage; }

	void AttributeState()
	{
		SetSkillStatus(m_skillname);

		if (INPUT->IsKeyDown('1'))		m_attribute = ATTRIBUTE_FIRE;
		if (INPUT->IsKeyDown('2'))		m_attribute = ATTRIBUTE_WATER;
		if (INPUT->IsKeyDown('3'))		m_attribute = ATTRIBUTE_ELECTRICITY;

		m_skillState = STATE_TYPE;
	}

	void TypeState()
	{
		if (INPUT->IsKeyDown('1'))	m_skilltype = TYPE_BOLT; 
		if (INPUT->IsKeyDown('2'))	m_skilltype = TYPE_WALL;
		if (INPUT->IsKeyDown('3'))	m_skilltype = TYPE_SHIELD;

		switch (m_skilltype)
		{
		case TYPE_BOLT:
			switch (m_attribute)
			{
				case ATTRIBUTE_FIRE:m_skillname = FIRE_BOLT;		break;
				case ATTRIBUTE_WATER:m_skillname = WATER_BOLT;					break;
				case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_BOLT;		break;
			}
			SetSkillStatus(m_skillname);
			m_skillState = STATE_BOLT;
			break;
		case TYPE_WALL: 
			switch (m_attribute)
			{
				case ATTRIBUTE_FIRE:m_skillname = FIRE_WALL;		break;
				case ATTRIBUTE_WATER:m_skillname = WATER_WALL;					break;
				case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_WALL;		break;
			}
			SetSkillStatus(m_skillname);
			m_skillState = STATE_WALL;
			break;
		case TYPE_SHIELD: 
			switch (m_attribute)
			{
				case ATTRIBUTE_FIRE:m_skillname = FIRE_SHIELD;					break;
				case ATTRIBUTE_WATER:m_skillname = WATER_SHIELD;				break;
				case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_SHIELD;	break;
			}
			SetSkillStatus(m_skillname);
			m_skillState = STATE_SHIELD;
			break;
		}
				
	}
	void StatusState()
	{
		m_skillState = STATE_STATUS;	
	}
	void BoltState(float deltaTime)
	{
		SetPosition(m_pos + m_dir*m_speed*deltaTime);
		SetsustainmentTime(1 / deltaTime);
		if(m_sustainmentTime<0.01f)m_skillState = STATE_ATTRIBUTE; m_skillname = SKILL_NONE;
	}

	void WallState(float deltaTime)
	{
		this->SetPosition(m_pos + m_dir*m_speed);
		SetsustainmentTime(1 / deltaTime);
		if (m_sustainmentTime < 0.01f)m_skillState = STATE_ATTRIBUTE; m_skillname = SKILL_NONE;
	}

	void ShieldState(float deltaTime)
	{
		this->SetPosition(m_pos);
		SetsustainmentTime(1/deltaTime);
		if (m_sustainmentTime<0.01f)m_skillState = STATE_ATTRIBUTE; m_skillname = SKILL_NONE;
	}

	void MonsterAttack(float delTatime)
	{
		SetPosition(m_pos + m_dir*m_speed*delTatime);
		SetsustainmentTime(1 / delTatime);
		if (m_sustainmentTime<0.01f)m_skillState = MONSTER_ATTACK; m_skillname = FIRE_BOLT;
	}

	void ColliedWithCharacter(Skill A,Character* pCharacter)
	{
		pCharacter->SetLife(-A.GetDamage());
	}
	
	void ColliedWithSkill(Skill A, Skill B)
	{
		AttributeMatch(A, B);

		A.SetLife(-B.GetDamage());
		B.SetLife(-A.GetDamage());

		if (A.m_life < 0.01f)
		{
			A.SetsustainmentTime(0);
		}

		if (B.m_life < 0.01f)
		{
			B.SetsustainmentTime(0);
		}
	}
};