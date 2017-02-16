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
	
	SKILL_STATE		m_skillState;
	SKILL_USER		m_skillUser;
	
	Object*			m_pcharacter;
	RotateDir*       m_rotateDir;

	int ExtraTime;
public:
	Skill(Object* pCharacter, SKILL_USER id,SKILL_LIST name) : Object(id)
	{
		m_Magic = new Magic(name);
		m_skillUser = id;
		m_pcharacter = pCharacter;
		m_dir = pCharacter->GetDir();
		m_pos = pCharacter->Position();
		switch (name)
		{
		case FIRE_BOLT:	m_skillState = STATE_BOLT;		case WATER_BOLT:	case ELECTRICITY_BOLT:			break;
		case FIRE_WALL:		case WATER_WALL:	case ELECTRICITY_WALL:		m_skillState = STATE_WALL;		break;
		case FIRE_SHIELD:	case WATER_SHIELD:	case ELECTRICITY_SHIELD:	m_skillState = STATE_SHIELD;	break;
		}
	
		m_rotateDir = new RotateDir();

		RENDER->LoadImageFiles(TEXT("Fire_Bolt"), TEXT("Image/Magic/Fire/Bolt/Bolt"), TEXT("png"), 11);
		RENDER->LoadImageFiles(TEXT("Attribute_Water"), TEXT("Image/Magic/Circle/Blue/Circle_Blue_"), TEXT("png"), 8);

		ExtraTime = 1;
	}
	~Skill()
	{
		delete m_Magic;
		OBJECT->DestroySkill(this);
	}


	void Update(float deltaTime)
	{
		Animation()->Update(deltaTime);
		switch (m_skillState)
		{
		case STATE_BOLT:		BoltState(deltaTime);		break;
		case STATE_WALL:		WallState(deltaTime);		break;
		case STATE_SHIELD:		ShieldState(deltaTime);		break;
		case STATE_VANISH:		VanishState(deltaTime);	break;
		case MONSTER_ATTACK:	MonsterAttack(deltaTime);	break;
		}
		m_rotateDir->Update(deltaTime);
		SetSkllTimer(deltaTime);
	}

	void Draw(Camera* pCamera)
	{

		ColorF color = ColorF::GhostWhite;
		Vector rotateDir = m_rotateDir->GetRotateDir();
		
		if (m_Magic->GetSkillName() == SKILL_NONE)
		{
			switch (m_skillState)
			{
			case STATE_BOLT:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_WALL:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case STATE_SHIELD:		pCamera->Draw(Animation()->Get(ATTRIBUTE_WATER)->GetSprite(), m_pcharacter->Position(), rotateDir); break;
			case MONSTER_ATTACK:	pCamera->DrawFillCircle(m_pcharacter->Position(), 30, ColorF::Yellow);			break;
			}
		}
		//cout << "스킬이름::"<<m_skillname << endl;

		switch (m_Magic->GetSkillName())
		{
		case SKILL_NONE:													break;
		case FIRE_BOLT:					pCamera->Draw(Animation()->Current()->GetSprite(), m_pos, m_dir);	break;
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

	void AttributeMatch(Magic* B)
	{
		switch (m_Magic->GetAttribute())
		{
		case ATTRIBUTE_FIRE:	
			if (B->GetAttribute() == ATTRIBUTE_WATER)			B->SetDamage(0);	
			else if (B->GetAttribute() == ATTRIBUTE_ELECTRICITY)this->m_Magic->SetDamage(0);	break;
		case ATTRIBUTE_WATER:		
			if (B->GetAttribute() == ATTRIBUTE_FIRE)			B->SetDamage(0);
			else if (B->GetAttribute() == ATTRIBUTE_ELECTRICITY)this->m_Magic->SetDamage(0);	break;
		case ATTRIBUTE_ELECTRICITY:	
			if (B->GetAttribute() == ATTRIBUTE_WATER)			B->SetDamage(0);
			else if (B->GetAttribute() == ATTRIBUTE_FIRE)this->m_Magic->SetDamage(0);	break;
		}
	}
	void BoltState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		//cout << "순서 5" << m_sustainmentTime<< endl;
		m_pos += m_dir*deltaTime*m_Magic->GetSpeed();
		this->SetCollider(m_pos, 100);
		if (IsGroundCollided())m_Magic->SetTIme(0);
		if (IsMonsterCollided()||IsPlayerCollided())
		{
			ColliedWithCharacter();
		}
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}
	//	if (m_Magic->GetTime() <= 0)m_skillState = STATE_VANISH;

	}

	void WallState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		
		Vector movedPos= m_pcharacter->Position() + m_dir*m_Magic->GetSpeed();;
		this->SetCollider(m_pos, 200);
		if (IsGroundCollided())
		{
			if (IsGroundCollided())movedPos = GroundPush(movedPos);
			m_pos = movedPos;
		}

		else m_pos = m_pcharacter->Position() + m_dir*m_Magic->GetSpeed();

		if (IsMonsterCollided() || IsPlayerCollided())
		{
			ColliedWithCharacter();
		}

		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}

		if (m_Magic->GetTime() <= 0)
		{
			delete m_Magic;
			OBJECT->DestroySkill(this);
		}


	}

	void ShieldState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		SetPosition(m_pcharacter->Position());
		this->SetCollider(m_pos, 100);
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}

		if (m_Magic->GetTime() <= 0)
		{
			delete m_Magic;
			OBJECT->DestroySkill(this);
		}


	}

	void SetExtratime(float time)
	{
		this->ExtraTime -= time;
	}

	void VanishState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());

		SetExtratime(deltaTime);
		if (ExtraTime < 0)
		{
			delete m_Magic;
			OBJECT->DestroySkill(this);
		}
	}

	void MonsterAttack(float delTatime)
	{
		//Animation()->Play(m_Magic->GetSkillName());
		//SetPosition(m_pos + m_dir*m_speed*delTatime);
		//SetsustainmentTime(360 * delTatime);
		//if (m_sustainmentTime < 0.001f)m_skillState = STATE_IDLE;
	}

	void ColliedWithCharacter()
	{
		if (m_skillUser == USER_PLAYER)
		{
			list<Object*> monsterList = OBJECT->GetMonsterList();
			FOR_LIST(Object*, monsterList)
			{
				if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
				{
					//(*it)->SetLife(-this->m_Magic->GetDamage());
				}
			}
		}
		else if (m_skillUser != USER_PLAYER)
		{
			//OBJECT->GetPlayer()->SetLife(-this->m_Magic->GetDamage());
		}
	}

	void ColliedWithSkill(Object* B)
	{

		AttributeMatch(B->GetMagic());


		m_Magic->SetLife(-B->GetMagic()->GetDamage());

		if (m_Magic->GetLife() <= 0)
		{
			m_Magic->SetTIme(0);
		}

		if (B->GetMagic()->GetLife() <= 0)
		{
			B->GetMagic()->SetTIme(0);
		}
	}

	void SetSkllTimer(float deltatime)
	{
		this->m_Magic->SetTimer(-deltatime*60);
	}

	bool IsGroundCollided()
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_GROUND);
		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				return true;
			}
		}
		return false;
	}

	bool IsMonsterCollided()
	{
		if (m_skillUser == USER_PLAYER)
		{
			list<Object*> monsterList = OBJECT->GetMonsterList();
			FOR_LIST(Object*, monsterList)
			{
				if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool IsPlayerCollided()
	{
		if (m_skillUser != USER_PLAYER)
		{
			if (MATH->IsCollided(this->getCircle(), OBJECT->GetPlayer()->Collider()))
			{
				return true;
			}
		}
		return false;
	}
	
	Object* isSkillCollided()
	{
		list<Object*> SkillList = OBJECT->GetSkillList();
		FOR_LIST(Object*, SkillList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				return (*it);
			}
		}
		return NULL;
	}

	Vector GroundPush(Vector movedPos)
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_GROUND);

		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				movedPos -= MATH->GetOverlappedVector(this->getCircle(), (*it)->Collider());
			}
		}
		return movedPos;
	}
};

