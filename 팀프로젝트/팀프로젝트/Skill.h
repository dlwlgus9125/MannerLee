#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Math.h"
#include "InputManager.h"

#define SKILL 

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

	Object* m_pcharacter;

public:
	Skill(Object* pCharacter, SKILL_LIST id) : Object(id)
	{
		m_skillname = id;
		m_pcharacter = pCharacter;
		m_dir = pCharacter->GetDir();
		m_pos = pCharacter->Position();
		m_skillState = STATE_IDLE;
		m_skilltype = TYPE_NONE;
		m_attribute = ATTRIBUTE_NONE;
		m_skillname = SKILL_NONE;
	}
	
	void SetSkillStatus(SKILL_LIST id)
	{
		switch (id)
		{
		case SKILL_NONE:
			m_pos=m_pcharacter->Position();
			m_speed = 0;
			m_damage = 0;
			m_life =0;
			m_sustainmentTime =0;
			break;
		case FIRE_BOLT:
			m_speed = 1000.0f;
			m_damage = 300.0f;
			m_life = 1.0f;
			m_sustainmentTime = 1.0f;
			break;
		case FIRE_WALL:
			m_speed =	300.0f;
			m_damage = 300.0f;
			m_life = 900.0f;
			m_sustainmentTime = 5.0f;
			break;
		case FIRE_SHIELD:
			m_speed = 0.0f;
			m_damage = 1.0f;
			m_life = 600.0f;
			m_sustainmentTime = 10.0f;
			break;
		case WATER_BOLT:
			m_speed = 1000.0f;
			m_damage = 300.0f;
			m_life = 1.0f;
			m_sustainmentTime = 1.0f;
			break;
		case WATER_WALL:
			m_speed = 300.0f;
			m_damage = 300.0f;
			m_life = 900.0f;
			m_sustainmentTime = 5.0f;
			break;
		case WATER_SHIELD:
			m_speed = 300.0f;
			m_damage = 300.0f;
			m_life = 600.0f;
			m_sustainmentTime = 10.0f;
			break;
		case ELECTRICITY_BOLT:
			m_speed = 1000.0f;
			m_damage = 300.0f;
			m_life = 1.0f;
			m_sustainmentTime = 1.0f;
			break;
		case ELECTRICITY_WALL:
			m_speed = 300.0f;
			m_damage = 300.0f;
			m_life =	900.0f;
			m_sustainmentTime = 5.0f;
			break;
		case ELECTRICITY_SHIELD:
			m_speed = 0.0f;
			m_damage = 0.0f;
			m_life = 600.0f;
			m_sustainmentTime = 10.0f;
			break;
		}

		m_skillname = id;
	}

	void Update(float deltaTime)
	{
		switch (m_skillState)
		{
		case STATE_IDLE:		IdleState();				break;
		case STATE_START:		CastStartState();			break;
		case STATE_ATTRIBUTE:	AttributeState();			break;
		case STATE_TYPE:		TypeState();				break;
		case STATE_BOLT:		BoltState(deltaTime);		break;
		case STATE_WALL:		WallState(deltaTime);		break;
		case STATE_SHIELD:		ShieldState(deltaTime);		break;
		case MONSTER_ATTACK:	MonsterAttack(deltaTime);	break;
		}

	}

	void Draw(Camera* pCamera)
	{

		switch (m_skillState)
		{
		case STATE_ATTRIBUTE:	pCamera->DrawCircle(m_pos, 100, ColorF::Blue,2);			break;
		case STATE_TYPE:		pCamera->DrawCircle(m_pos, 100, ColorF::Red);		break;
		case MONSTER_ATTACK:	pCamera->DrawFillCircle(m_pos, 30, ColorF::Yellow);			break;
		case STATE_BOLT:		pCamera->DrawCircle(m_pos, 100, ColorF::Yellow);	break;
		case STATE_WALL:		pCamera->DrawCircle(m_pos, 100, ColorF::HotPink);	break;
		case STATE_SHIELD:		pCamera->DrawCircle(m_pos, 100, ColorF::RosyBrown); break;

		}

		switch (m_attribute)
		{
		
		}

		switch (m_skillname)
		{
		case SKILL_NONE:													break;
		case FIRE_BOLT:					pCamera->DrawFillCircle(m_pcharacter->Position(), 30, ColorF::Red);														break;
		case FIRE_WALL:					pCamera->DrawFillCircle(m_pcharacter->Position(), 30, ColorF::Yellow);											break;
		case FIRE_SHIELD:													break;
		case WATER_BOLT:													break;
		case WATER_WALL:													break;
		case WATER_SHIELD:													break;
		case ELECTRICITY_BOLT:												break;
		case ELECTRICITY_WALL:												break;
		case ELECTRICITY_SHIELD:											break;
		}

		
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
	void SetsustainmentTime(float time) { m_sustainmentTime * time; }
	float GetDamage() { return m_damage; }

	void AttributeState()
	{
		SetSkillStatus(m_skillname);

		if (INPUT->IsKeyDown('1'))		m_attribute = ATTRIBUTE_FIRE;	m_skillState = STATE_TYPE;
		if (INPUT->IsKeyDown('2'))		m_attribute = ATTRIBUTE_WATER;	m_skillState = STATE_TYPE;
		if (INPUT->IsKeyDown('3'))		m_attribute = ATTRIBUTE_ELECTRICITY;	m_skillState = STATE_TYPE;

	
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
				case ATTRIBUTE_FIRE:m_skillname = FIRE_BOLT;					break;
				case ATTRIBUTE_WATER:m_skillname = WATER_BOLT;					break;
				case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_BOLT;		break;
			}
			SetSkillStatus(m_skillname);
			m_skillState = STATE_BOLT;
			break;
		case TYPE_WALL: 
			switch (m_attribute)
			{
				case ATTRIBUTE_FIRE:m_skillname = FIRE_WALL;					break;
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

	void BoltState(float deltaTime)
	{
		SetPosition(m_pos + m_dir*m_speed*deltaTime);
		SetsustainmentTime(1 / deltaTime);
		switch (m_attribute)
		{
		case ATTRIBUTE_NONE:break;
		case ATTRIBUTE_FIRE:break;
		case ATTRIBUTE_WATER:break;
		case ATTRIBUTE_ELECTRICITY:break;
		}
		if (m_sustainmentTime < 0.01f)
		{
			m_skillState = STATE_IDLE; 
		}
		
	}

	void WallState(float deltaTime)
	{
		this->SetPosition(m_pos + m_dir*m_speed);

		switch (m_attribute)
		{
		case ATTRIBUTE_NONE:break;
		case ATTRIBUTE_FIRE:break;
		case ATTRIBUTE_WATER:break;
		case ATTRIBUTE_ELECTRICITY:break;
		}
		SetsustainmentTime(1 / deltaTime);
		if (m_sustainmentTime < 0.01f)m_skillState = STATE_IDLE;
	}

	void ShieldState(float deltaTime)
	{
		this->SetPosition(m_pos);

		switch (m_attribute)
		{
		case ATTRIBUTE_NONE:break;
		case ATTRIBUTE_FIRE:break;
		case ATTRIBUTE_WATER:break;
		case ATTRIBUTE_ELECTRICITY:break;
		}

		SetsustainmentTime(1/deltaTime);
		if (m_sustainmentTime<0.01f)m_skillState = STATE_IDLE;
	}

	void MonsterAttack(float delTatime)
	{
		SetPosition(m_pos + m_dir*m_speed*delTatime);
		SetsustainmentTime(1 / delTatime);
		if (m_sustainmentTime<0.01f)m_skillState = MONSTER_ATTACK;
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

	void CastStartState()
	{
		
		if (INPUT->IsKeyDown('1'))m_skillState = STATE_ATTRIBUTE;
	}

	void IdleState()
	{
		if (INPUT->IsKeyDown('1'))
		{
			m_skillState = STATE_START;
		}
		SetSkillStatus(SKILL_NONE);
	}
};