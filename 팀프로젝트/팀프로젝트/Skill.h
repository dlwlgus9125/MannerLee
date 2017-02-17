#pragma once
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Math.h"
#include "InputManager.h"
#include "UIManager.h"
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

	SKILL_STATE      m_skillState;
	SKILL_USER      m_skillUser;

	Object*         m_pcharacter;
	RotateDir*       m_rotateDir;

	Circle m_Circle;
	Magic* m_Magic;
	int m_Timer;
	bool m_isComplete;
public:
	Skill(Object* pCharacter, SKILL_USER id, SKILL_LIST name) : Object(id)
	{
		
		
		m_Magic = new Magic(name);
		m_Timer = m_Magic->GetTime()*60;
		m_skillUser = id;
		m_pcharacter = pCharacter;
		m_pos = pCharacter->Position();
		m_dir = m_pcharacter->GetDir();
		Vector targetPos = RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos());
		if (id == USER_PLAYER&&UI->Setting()==MOUSE)
		{
			m_dir = (targetPos - m_pos).Normalize();
		}
		
		m_isComplete = false;
		switch (name)
		{
		case FIRE_BOLT:      case WATER_BOLT:   case ELECTRICITY_BOLT:      m_skillState = STATE_BOLT;      break;
		case FIRE_WALL:      case WATER_WALL:   case ELECTRICITY_WALL:		m_pos = targetPos;   m_skillState = STATE_WALL;      break;
		case FIRE_SHIELD:   case WATER_SHIELD:   case ELECTRICITY_SHIELD:   m_skillState = STATE_SHIELD;   break;
		}

		m_rotateDir = new RotateDir();

		RENDER->LoadImageFiles(TEXT("Fire_Bolt"), TEXT("Image/Magic/Fire/Bolt/Bolt"), TEXT("png"), 11);
		RENDER->LoadImageFiles(TEXT("Attribute_Water"), TEXT("Image/Magic/Circle/Blue/Circle_Blue_"), TEXT("png"), 8);
		SOUND->LoadFile("Explosion1", "Sound/Effect/Explosion1.wav", false);
	}



	void Update(float deltaTime)
	{
		Animation()->Update(deltaTime);
		switch (m_skillState)
		{
		case STATE_BOLT:      BoltState(deltaTime);      break;
		case STATE_WALL:      WallState(deltaTime);      break;
		case STATE_SHIELD:      ShieldState(deltaTime);      break;
		case STATE_VANISH:      VanishState(deltaTime);   break;
		case MONSTER_ATTACK:   MonsterAttack(deltaTime);   break;
		}
		m_rotateDir->Update(deltaTime);
		SetTimer();
	}

	void Draw(Camera* pCamera)
	{
		

		ColorF color = ColorF::GhostWhite;
		Vector rotateDir = m_rotateDir->GetRotateDir();

		//cout << "스킬이름::"<<m_skillname << endl;

		switch (m_Magic->GetSkillName())
		{
		case SKILL_NONE:                                       break;
		case FIRE_BOLT:               pCamera->Draw(Animation()->Current()->GetSprite(), m_pos, m_dir);  
										pCamera->DrawCircle(m_Circle.center, m_Circle.radius, ColorF::Red, 2.0f); break;
		case FIRE_WALL:               pCamera->DrawFillCircle(m_pos, 300, ColorF::Blue);   break;
		case FIRE_SHIELD:            pCamera->DrawCircle(m_pos, 100, ColorF::Yellow, 2);   break;
		case WATER_BOLT:                                       break;
		case WATER_WALL:                                       break;
		case WATER_SHIELD:                                       break;
		case ELECTRICITY_BOLT:                                    break;
		case ELECTRICITY_WALL:                                    break;
		case ELECTRICITY_SHIELD:                                 break;
		}


	}

	void AttributeMatch(Object* MagicB)
	{
		Magic* B = MagicB->GetMagic();

		switch (m_Magic->GetAttribute())
		{
		case ATTRIBUTE_FIRE:
			if (B->GetAttribute() == ATTRIBUTE_WATER)        MagicB->SetTimer(-1000);
			else if (B->GetAttribute() == ATTRIBUTE_ELECTRICITY)this->SetTimer(-1000);   break;
		case ATTRIBUTE_WATER:
			if (B->GetAttribute() == ATTRIBUTE_FIRE)        MagicB->SetTimer(-1000);
			else if (B->GetAttribute() == ATTRIBUTE_ELECTRICITY)this->SetTimer(-1000);   break;
		case ATTRIBUTE_ELECTRICITY:
			if (B->GetAttribute() == ATTRIBUTE_WATER)         MagicB->SetTimer(-1000);
			else if (B->GetAttribute() == ATTRIBUTE_FIRE)this->SetTimer(-1000);   break;
		}
	}
	void BoltState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		m_pos += m_dir*deltaTime*m_Magic->GetSpeed();
		this->SetCollider(m_pos, 10);
		if (IsGroundCollided())
		{
			RENDER->GetCamera(CAM_MAIN)->SetIsWaveTrue();
			m_isComplete = true;
			m_Magic->SetTIme(0);
		}
		if (IsMonsterCollided()||IsPlayerCollided())
		{
			RENDER->GetCamera(CAM_MAIN)->SetIsWaveTrue();
			ColliedWithCharacter();
			m_isComplete = true;			
		}
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}
		if(m_Timer<=0) m_isComplete = true;

	}

	void WallState(float deltaTime)
	{
		//Animation()->Play(m_Magic->GetSkillName());
		
		
		if (m_Timer <= 0) m_isComplete = true;

		this->SetCollider(m_pos, 20);

		if (IsMonsterCollided() || IsPlayerCollided())
		{
			ColliedWithCharacter();
		}

		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}

		if (IsGroundCollided())
		{

		}
		

	}

	void ShieldState(float deltaTime)
	{
		//Animation()->Play(m_Magic->GetSkillName());
		m_pos = m_pcharacter->Position();
		this->SetCollider(m_pos, 100);
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}


		if (m_Timer <= 0) m_isComplete = true;

	}

	void VanishState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());

	
		
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
				if (MATH->IsCollided(this->getCircle(), (*it)->getCircle()))
				{
					cout << "충돌" << endl;
					SOUND->Play("Explosion1", 2.0f);
					(*it)->SetLife(-this->m_Magic->GetDamage());
				}
			}
		}
		else if (m_skillUser != USER_PLAYER)
		{
			//SOUND->Play("Explosion1", 2.0f);
			OBJECT->GetPlayer()->SetLife(this->m_Magic->GetDamage());
		}
	}

	void ColliedWithSkill(Object* B)
	{

		AttributeMatch(B);


		m_Magic->SetLife(-B->GetMagic()->GetDamage());
		B->GetMagic()->SetLife(m_Magic->GetDamage());

		if (m_Magic->GetSkillType() == TYPE_SHIELD&&B->GetMagic()->GetSkillType() == TYPE_BOLT)
		{
			B->GetMagic()->SetLife(-100);
		}

		if (m_Magic->GetLife() <= 0)
		{
			this->SetTimer(-100);
		}

		if (B->GetMagic()->GetLife() <= 0)
		{
			B->SetTimer(-100);
		}
	}

	void SetSkllTimer(float deltatime)
	{
		this->m_Magic->SetTimer(deltatime);
	}

	bool IsGroundCollided()
	{
		list<Object*> groundList = OBJECT->GetPropsList(OBJ_GROUND);
		FOR_LIST(Object*, groundList)
		{
			if (MATH->IsCollided(this->getCircle(), (*it)->Collider()))
			{
				SOUND->Play("Explosion1", 2.0f);
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
				if (MATH->IsCollided(this->getCircle(), (*it)->getCircle()))
				{
					SOUND->Play("Explosion1", 2.0f);
					OBJECT->DestroyMonster((*it));
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
			if (MATH->IsCollided(this->getCircle(), OBJECT->GetPlayer()->getCircle()))
			{
				SOUND->Play("Explosion1", 2.0f);
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
			if (MATH->IsCollided(this->getCircle(), (*it)->getCircle()))
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

	Circle getCircle() { return m_Circle; }
	Magic* GetMagic() { return m_Magic; }
	bool GetIsComplete() { return m_isComplete; }

	void SetCollider(Vector center, float radius)
	{
		m_Circle = Circle(center, radius);
	}
	void SetTimer(float num = 1)
	{
		m_Timer -= num;
	}
};
