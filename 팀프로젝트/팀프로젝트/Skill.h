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
	Magic* m_prev;
	Magic* m_Magic;
	int m_Timer;
	bool  m_isComplete;
	bool  m_isPlayerHit;
	
public:
	Skill(Object* pCharacter, SKILL_USER id, SKILL_LIST name,int gage) : Object(id)
	{
		
		
		m_Magic = new Magic(name);
		m_Timer = m_Magic->GetTime()*60;
		m_skillUser = id;
		m_pcharacter = pCharacter;
		
	
		
		Vector targetPos = RENDER->GetCamera(CAM_MAIN)->ScreenToWorldPos(INPUT->GetMousePos());
	
	
		m_pos = pCharacter->Position();
		if (gage == 2)m_pos = m_pos + Vector(20, 20);
		if (gage == 3)m_pos = m_pos - Vector(20, 20);
		m_dir = m_pcharacter->GetDir();		
		if (id == USER_PLAYER)
		{
			m_dir = (targetPos - m_pos).Normalize();
		}

		

		m_isComplete = false;
		m_isPlayerHit = false;
		switch (name)
		{
		case FIRE_BOLT:      case WATER_BOLT:   case ELECTRICITY_BOLT:      m_skillState = STATE_BOLT;      break;
		case FIRE_WALL:      case WATER_WALL:   case ELECTRICITY_WALL:	
			if (gage == 3)m_pos = targetPos+Vector(10, 20);
			if (gage == 2)m_pos = targetPos-Vector(20, 10);
			if(gage==1)m_pos = targetPos; m_skillState = STATE_WALL;
			break;

		case FIRE_SHIELD:   case WATER_SHIELD:   case ELECTRICITY_SHIELD:   m_skillState = STATE_SHIELD;   break;
		case ETERNAL_FIRE_WALL://m_pos = ; m_skillState=STATE_WALL;
			break;
		}

		m_rotateDir = new RotateDir();


	}



	void Update(float deltaTime)
	{
		Animation()->Update(deltaTime);
		
		switch (m_skillState)
		{
		case STATE_BOLT:      BoltState(deltaTime);      break;
		case STATE_WALL:      WallState(deltaTime);      break;
		case STATE_SHIELD:    ShieldState(deltaTime);      break;
		case STATE_EXPLOSION: ExplosionState(deltaTime);      break;
		}
		StopSoundMachine();
		m_rotateDir->Update(deltaTime);
		SetTimer();
	}

	void Draw(Camera* pCamera)
	{
		if(m_isPlayerHit)pCamera->Draw(Animation()->Get(100)->GetSprite(), pCamera->GetLeftTop(), Vector::Right(), 0.3f);
		ColorF color = ColorF::GhostWhite;
		Vector rotateDir = m_rotateDir->GetRotateDir();

		//cout << "스킬이름::"<<m_skillname << endl;

		switch (m_Magic->GetSkillType())
		{
		case TYPE_BOLT:               pCamera->Draw(Animation()->Current()->GetSprite(), m_pos, m_dir); 
			                          pCamera->DrawCircle(m_Circle.center, m_Circle.radius, ColorF::Red, 2.0f); break;
		default:pCamera->Draw(Animation()->Current()->GetSprite(), Position()); break;
		}


	}

	void AttributeMatch(Object* MagicB)
	{
		Magic* B = MagicB->GetMagic();

		if (this->GetMagic()->GetAttribute() == B->GetAttribute())
		{
			m_isComplete = true;
			MagicB->SetIsComplete();
		}
		else
		{
			switch (m_Magic->GetAttribute())
			{
			case ATTRIBUTE_FIRE:
				 if (B->GetAttribute() == ATTRIBUTE_WATER)m_isComplete = true; break;
			case ATTRIBUTE_WATER:
				if (B->GetAttribute() == ATTRIBUTE_ELECTRICITY)m_isComplete = true; break;
			case ATTRIBUTE_ELECTRICITY:
				 if (B->GetAttribute() == ATTRIBUTE_FIRE)m_isComplete = true; break;
		
		}
		}
		
	}
	void BoltState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		m_pos += m_dir*deltaTime*m_Magic->GetSpeed();
		this->SetCollider(m_pos, 10);
		if (IsGroundCollided())
		{
			SoundCorrecter();
			SetTimer(60);
			m_skillState = STATE_EXPLOSION;
		}
		if (IsMonsterCollided()||IsPlayerCollided())
		{

			SoundCorrecter();
			ColliedWithCharacter();
			SetTimer(60);
			m_skillState = STATE_EXPLOSION;
		}
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}
		if(m_Timer<0) m_isComplete = true;

	}

	void WallState(float deltaTime)
	{
		Animation()->Play(m_Magic->GetSkillName());
		SoundCorrecter();
		

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

		if (IsGroundCollided()!=false)
		{
			
			
		}
		

	}

	void ShieldState(float deltaTime)
	{	
		if (OBJECT->GetShieldList().size()>1)
		{
			OBJECT->GetShieldList().front()->SetIsComplete();
		}
		Animation()->Play(m_Magic->GetSkillName());
		SoundCorrecter();///
	
		m_pos = m_pcharacter->Position();
		this->SetCollider(m_pos, 40);
		if (isSkillCollided() != NULL)
		{
			ColliedWithSkill(isSkillCollided());
		}


		if (m_Timer <= 0) m_isComplete = true;

	}

	void ExplosionState(float deltaTime)
	{
		if (m_Magic->GetAttribute() == ATTRIBUTE_FIRE)Animation()->Play(FIRE_EXPLOSION);
		if (m_Magic->GetAttribute() == ATTRIBUTE_WATER)Animation()->Play(WATER_EXPLOSION);
		if (m_Magic->GetAttribute() == ATTRIBUTE_ELECTRICITY)Animation()->Play(ELECTRICITY_EXPLOSION);
		RENDER->GetCamera(CAM_MAIN)->SetIsWaveTrue();
		
		if (m_Timer <= 0) m_isComplete = true;
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
					if (this->GetMagic()->GetSkillType() == TYPE_WALL)
					{
						if (m_Timer == 240)
						{ 
							(*it)->SetLife(-this->m_Magic->GetDamage());
							if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
							if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
							if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
						}
						if (m_Timer == 180)	
						{ 
							(*it)->SetLife(-this->m_Magic->GetDamage());
							if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
							if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
							if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
						}
						if (m_Timer == 120)
						{
							(*it)->SetLife(-this->m_Magic->GetDamage());
							if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
							if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
							if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
						}
						if (m_Timer == 60)	
						{
							if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
							if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
							if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
							(*it)->SetLife(-this->m_Magic->GetDamage());
						}
						if (m_Timer == 1)
						{ 
							if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
							if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
							if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
							(*it)->SetLife(-this->m_Magic->GetDamage());
						}
					}
					if (this->GetMagic()->GetSkillType() == TYPE_BOLT) 
					{
						if ((*it)->ID() == OBJ_MONSTER)SOUND->Play("MonsterHit", 2.0f);
						if ((*it)->ID() == OBJ_BOSS)SOUND->Play("BossHit", 2.0f);
						if ((*it)->GetLife() <= 0 && (*it)->ID() != OBJ_BOSS)OBJECT->DestroyMonster((*it));
						(*it)->SetLife(-this->m_Magic->GetDamage());
					}
				}
			}
		}
		else if (m_skillUser != USER_PLAYER)
		{
			SOUND->Play("Hit", 2.0f);
			m_isPlayerHit = true;
			OBJECT->GetPlayer()->SetLife(this->m_Magic->GetDamage());
		}
	}

	void ColliedWithSkill(Object* B)
	{
		AttributeMatch(B);
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
				if (MATH->IsCollided(this->getCircle(), (*it)->getCircle()))
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
			if (MATH->IsCollided(this->getCircle(), OBJECT->GetPlayer()->getCircle()))
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
			if (MATH->IsCollided(this->getCircle(), (*it)->getCircle()))
			{
				if((*it)->ID()!=this->ID())return (*it);
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
		m_Timer--;
		if (num != 1) m_Timer = num;
	}

	void ChangeShield(Object* prev)
	{
		if (prev->GetMagic()->GetSkillType() == TYPE_SHIELD)
		{
			prev->SetIsComplete();
		}
	}

	void SoundCorrecter()
	{
		switch (m_Magic->GetSkillName())
		{
		case FIRE_BOLT:          SOUND->Play("Explosion_Fire",0.5f); break;
		case WATER_BOLT:         SOUND->Play("Explosion_Water",0.5f); break;
		case ELECTRICITY_BOLT:   SOUND->Play("Explosion_Electricity",0.5f); break;
		case FIRE_SHIELD:        if (SOUND->FindChannel("Shield_Fire") == NULL)SOUND->Play("Shield_Fire",0.5f); break;
		case WATER_SHIELD:       if (SOUND->FindChannel("Shield_Water") == NULL)SOUND->Play("Shield_Water",0.5f); break;
		case ELECTRICITY_SHIELD: if (SOUND->FindChannel("Shield_Electricity") == NULL)SOUND->Play("Shield_Electricity",0.5f); break;
		case FIRE_WALL:        if (SOUND->FindChannel("Wall_Fire") == NULL)SOUND->Play("Wall_Fire",0.5f); break;
		case WATER_WALL:       if (SOUND->FindChannel("Wall_Water") == NULL)SOUND->Play("Wall_Water",0.5f); break;
		case ELECTRICITY_WALL: if (SOUND->FindChannel("Wall_Electricity") == NULL)SOUND->Play("Wall_Electricity",0.5f); break;
		}
	}

	void StopSoundMachine()
	{
		if (m_Timer <= 0)
		{
			switch (m_Magic->GetSkillName())
			{
			case FIRE_SHIELD:        SOUND->Stop("Shield_Fire"); break;
			case WATER_SHIELD:       SOUND->Stop("Shield_Water"); break;
			case ELECTRICITY_SHIELD: SOUND->Stop("Shield_Electricity"); break;
			case FIRE_WALL:          SOUND->Stop("Wall_Fire"); break;
			case WATER_WALL:         SOUND->Stop("Wall_Water"); break;
			case ELECTRICITY_WALL:   SOUND->Stop("Wall_Electricity"); break;
			}
		}
	}
	void SetIsComplete()
	{
		m_isComplete = true;
	}
	int ID() { return m_skillUser; }

	
};
//FIRE_BOLT = 11, FIRE_SHIELD = 12, FIRE_WALL = 13, FIRE_EXPLOSION,
//WATER_BOLT = 21, WATER_SHIELD = 22, WATER_WALL = 23, WATER_EXPLOSION,
//ELECTRICITY_BOLT = 31, ELECTRICITY_SHIELD = 32, ELECTRICITY_WALL = 33, ELECTRICITY_EXPLOSION,