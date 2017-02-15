#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Math.h"
#include "InputManager.h"

#define SKILL 

//단위벡터 회전
class RotateDir
{
	Vector m_point;
	float m_distance;

	Vector m_dir;
	float m_angle;
	float m_rotateSpeed;

public:
	RotateDir()
	{
		m_point = Vector(100, 100);
		m_distance = 100;
		m_dir = Vector::Right();
		m_angle = 0;
		m_rotateSpeed = 150;
	}

	void Update(float deltaTime)
	{
		//dir회전
		m_angle += m_rotateSpeed * deltaTime;
		//cout << m_angle << endl;
		m_dir = (m_point + MATH->ToDirection(m_angle) * m_distance).Normalize();
		//cout << m_dir.x << ", " << m_dir.y << endl;
	}
	

	Vector GetRotateDir() { return m_dir; }

};


class Skill : public Object
{
	SKILL_ATTRIBUTE m_attribute;
	SKILL_TYPE		m_skilltype;

	float           m_damage;
	float           m_speed;
	float			m_life;
	int				m_sustainmentTime;
	SKILL_STATE		m_skillState;
	SKILL_LIST		m_skillname;

	Vector			m_pos;
	Vector          m_dir;
	Vector			skillsize;

	Object*			m_pcharacter;

	RotateDir*       m_rotateDir;
	
	int m_Second;

public:
	Skill(Object* pCharacter, SKILL_USER id) : Object(id)
	{
		m_skillname = SKILL_NONE;
		m_pcharacter = pCharacter;
		m_dir = pCharacter->GetDir();
		m_pos = pCharacter->Position();
		m_skillState = STATE_IDLE;
		m_skilltype = TYPE_NONE;
		m_attribute = ATTRIBUTE_NONE;
		m_skillname = SKILL_NONE;
		m_Second = timeGetTime() / 1000 % 60;
		m_rotateDir = new RotateDir();

		RENDER->LoadImageFiles(TEXT("Fire_Bolt"), TEXT("Image/Magic/Fire/Bolt/Bolt"), TEXT("png"), 11);
		

	}

	void SetSkillStatus(SKILL_LIST id)
	{
		switch (id)
		{
		case SKILL_NONE:
			m_pos = m_pcharacter->Position();
			m_speed = 0;
			m_damage = 0;
			m_life = 0;
			m_sustainmentTime = 0;
			m_attribute = ATTRIBUTE_NONE;
			m_skilltype = TYPE_NONE;
			break;
		case FIRE_BOLT:
			m_speed = 1000.0f;
			m_damage = 300.0f;
			m_life = 1.0f;
			m_sustainmentTime = 1.0f;
			break;
		case FIRE_WALL:
			m_speed = 200.0f;
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
			m_speed = 200.0f;
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
			m_speed = 200.0f;
			m_damage = 300.0f;
			m_life = 900.0f;
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
		Animation()->Update(deltaTime);
		switch (m_skillState)
		{
		case STATE_IDLE:		IdleState();				break;
		
		}
		m_rotateDir->Update(deltaTime);
		Animation()->Get(ATTRIBUTE_WATER)->Update(deltaTime);
		
		cout << "success" << endl;

	}

	void Draw(Camera* pCamera)
	{

		ColorF color = ColorF::GhostWhite;
		Vector rotateDir = m_rotateDir->GetRotateDir();
		if (m_skillname == SKILL_NONE)
		{
			switch (m_skillState)
			{
				
			case STATE_ATTRIBUTE:	pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_TYPE:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_BOLT:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_WALL:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_SHIELD:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case MONSTER_ATTACK:	pCamera->DrawFillCircle(m_pcharacter->Position(), 30, ColorF::Yellow);			break;
			}
		}
		//cout << "스킬이름::"<<m_skillname << endl;

		switch (m_skillname)
		{
		case SKILL_NONE:													break;
		case FIRE_BOLT:		pCamera->Draw(Animation()->Current()->GetSprite(), m_pos, m_dir);	break;
		case FIRE_WALL:					pCamera->DrawFillCircle(m_pos, 100, ColorF::Blue);	break;
		case FIRE_SHIELD:				pCamera->DrawCircle(m_pos, 150, ColorF::Yellow, 2);	break;
		case WATER_BOLT:													break;
		case WATER_WALL:													break;
		case WATER_SHIELD:													break;
		case ELECTRICITY_BOLT:												break;
		case ELECTRICITY_WALL:												break;
		case ELECTRICITY_SHIELD:											break;
		}


	}

	void AttributeMatch(Skill a, Skill b)
	{
		if (a.m_attribute == ATTRIBUTE_FIRE&&b.m_attribute == ATTRIBUTE_WATER)
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

	void SetDamage(float damage) { m_damage *= damage; }
	void SetLife(float damage) { m_life -= damage; }
	void SetsustainmentTime(float time) { m_sustainmentTime *= time; }
	float GetDamage() { return m_damage; }

	void AttributeState()
	{
		//	cout << "순서 3" << endl;


		int key = 0;
		//if (INPUT->IsKeyDown('1'))	key = 1;
		//if (INPUT->IsKeyDown('2'))	key = 2;
		//if (INPUT->IsKeyDown('3'))	key = 3;
		switch (key)
		{
		case 0:m_skillState = STATE_ATTRIBUTE; break;
		case 1:m_attribute = ATTRIBUTE_FIRE; m_skillState = STATE_TYPE; break;
		case 2:m_attribute = ATTRIBUTE_WATER; m_skillState = STATE_TYPE; break;
		case 3:m_attribute = ATTRIBUTE_ELECTRICITY; m_skillState = STATE_TYPE; break;
		}
	}

	void TypeState()
	{

		//if (INPUT->IsKeyDown('1'))	m_skilltype = TYPE_BOLT;
		//if (INPUT->IsKeyDown('2'))	m_skilltype = TYPE_WALL;
		//if (INPUT->IsKeyDown('3'))	m_skilltype = TYPE_SHIELD;
		/*cout << "스킬타입 : " << m_skilltype << endl;
		cout << "스킬타입 : " << m_skilltype << endl;
		cout << "순서 4" << endl;*/
		m_pos = m_pcharacter->Position();
		m_dir = m_pcharacter->GetDir();
		switch (m_skilltype)
		{
		case TYPE_NONE:				m_skillState = STATE_TYPE; break;
		case TYPE_BOLT:
			switch (m_attribute)
			{
			case ATTRIBUTE_FIRE:m_skillname = FIRE_BOLT;					break;
			case ATTRIBUTE_WATER:m_skillname = WATER_BOLT;					break;
			case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_BOLT;		break;
			}
			SetSkillStatus(m_skillname);
			if (INPUT->IsKeyDown('A'))
			{
				m_skillState = STATE_BOLT;
			}
			break;
		case TYPE_WALL:
			switch (m_attribute)
			{
			case ATTRIBUTE_FIRE:m_skillname = FIRE_WALL;					break;
			case ATTRIBUTE_WATER:m_skillname = WATER_WALL;					break;
			case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_WALL;		break;
			}
			SetSkillStatus(m_skillname);
			m_pos += m_dir*m_speed;
			if (INPUT->IsKeyDown('A'))
			{
				m_skillState = STATE_WALL;
			}
			break;
		case TYPE_SHIELD:
			switch (m_attribute)
			{
			case ATTRIBUTE_FIRE:m_skillname = FIRE_SHIELD;					break;
			case ATTRIBUTE_WATER:m_skillname = WATER_SHIELD;				break;
			case ATTRIBUTE_ELECTRICITY:m_skillname = ELECTRICITY_SHIELD;	break;
			}
			SetSkillStatus(m_skillname);
			if (INPUT->IsKeyDown('A'))
			{
				m_skillState = STATE_SHIELD;
			}
			break;
		}

	}

	void BoltState(float deltaTime)
	{
		cout << "여기 잇음" << endl;
		Animation()->Play(FIRE_BOLT);
		//cout << "순서 5" << m_sustainmentTime<< endl;
		m_pos += m_dir*deltaTime*m_speed;
		SetsustainmentTime(60 * deltaTime);
		if (m_sustainmentTime < 0.01f)m_skillState = STATE_IDLE;
	}

	void WallState(float deltaTime)
	{
		SetsustainmentTime(60 * deltaTime);
		if (m_sustainmentTime < 0.001f)m_skillState = STATE_IDLE;
	}

	void ShieldState(float deltaTime)
	{
		m_pos = m_pcharacter->Position();
		SetsustainmentTime(60 * deltaTime);
		if (m_sustainmentTime < 0.001f)m_skillState = STATE_IDLE;
	}

	void MonsterAttack(float delTatime)
	{
		SetPosition(m_pos + m_dir*m_speed*delTatime);
		SetsustainmentTime(360 * delTatime);
		if (m_sustainmentTime < 0.001f)m_skillState = STATE_IDLE;
	}

	//void ColliedWithCharacter(Skill A, Character* pCharacter)
	//{
	//	pCharacter->SetLife(-A.GetDamage());
	//}

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

	void IdleState()
	{
		
	}

};

