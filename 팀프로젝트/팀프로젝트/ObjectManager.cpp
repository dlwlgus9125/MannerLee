#include "ObjectManager.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Skill.h"



void ObjectManager::CreatePlayer(Vector pos, float colRadius)
{
	NEW_OBJECT(m_pPlayer, Player(OBJ_PLAYER));
	m_pPlayer->SetPosition(pos);
	m_pPlayer->SetCharacterCollider(colRadius);
	m_pPlayer->Animation()->Register(IDLE_UP, new Animation(TEXT("Idle_Up"), 1, 10, true, 2.0f));
	m_pPlayer->Animation()->Register(IDLE_LEFT, new Animation(TEXT("Idle_Left"), 1, 10, true, 2.0f));
	m_pPlayer->Animation()->Register(IDLE_RIGHT, new Animation(TEXT("Idle_Right"), 1, 10, true, 2.0f));
	m_pPlayer->Animation()->Register(IDLE_DOWN, new Animation(TEXT("Idle_Down"), 1, 10, true, 2.0f));

	m_pPlayer->Animation()->Register(RUN_UP, new Animation(TEXT("Run_Up"), 3, 5, true, 2.0f));
	m_pPlayer->Animation()->Register(RUN_LEFT, new Animation(TEXT("Run_Left"), 3, 5, true, 2.0f));
	m_pPlayer->Animation()->Register(RUN_RIGHT, new Animation(TEXT("Run_Right"), 3, 5, true, 2.0f));
	m_pPlayer->Animation()->Register(RUN_DOWN, new Animation(TEXT("Run_Down"), 3, 5, true, 2.0f));

	m_pPlayer->Animation()->Register(ATTRIBUTE_NONE, new Animation(TEXT("Attribute_None"), 8, 10, true, 0.7f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_FIRE, new Animation(TEXT("Attribute_Fire"), 8, 10, true, 0.7f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_WATER, new Animation(TEXT("Attribute_Water"), 8, 10, true, 0.7f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_ELECTRICITY, new Animation(TEXT("Attribute_Electricity"), 8, 10, true, 0.7f));

}

void ObjectManager::DestroyPlayer()
{
	DELETE_OBJECT(m_pPlayer);
}

void ObjectManager::CreateMonster(int id, MONSTER_KIND kind, Vector pos, float colRadius)
{
	NEW_OBJECT(Object* monster, Monster(id));
	monster->SetPosition(pos);
	monster->SetCharacterCollider(colRadius);
	monster->SetStandPosition();
	monster->SetMonsterKind(kind);

	monster->LoadingMonsterImage();
	monster->Animation()->Register(MINION_IDLE_UP, new Animation(TEXT("Minion_Idle_Up"), 1, 10, true, 2.0f));
	monster->Animation()->Register(MINION_IDLE_LEFT, new Animation(TEXT("Minion_Idle_Left"), 1, 10, true, 2.0f));
	monster->Animation()->Register(MINION_IDLE_RIGHT, new Animation(TEXT("Minion_Idle_Right"), 1, 10, true, 2.0f));
	monster->Animation()->Register(MINION_IDLE_DOWN, new Animation(TEXT("Minion_Idle_Down"), 1, 10, true, 2.0f));

	monster->Animation()->Register(MINION_RUN_UP, new Animation(TEXT("Minion_Run_Up"), 3, 5, true, 2.0f));
	monster->Animation()->Register(MINION_RUN_LEFT, new Animation(TEXT("Minion_Run_Left"), 3, 5, true, 2.0f));
	monster->Animation()->Register(MINION_RUN_RIGHT, new Animation(TEXT("Minion_Run_Right"), 3, 5, true, 2.0f));
	monster->Animation()->Register(MINION_RUN_DOWN, new Animation(TEXT("Minion_Run_Down"), 3, 5, true, 2.0f));

	m_monsterList.push_back(monster);
}

void ObjectManager::DestroyAllMonster()
{
	FOR_LIST(Object*, m_monsterList)
	{
		DELETE_OBJECT((*it));
	}
	m_monsterList.clear();
}

void ObjectManager::DestroyMonster(Object* pMonster)
{
	m_monsterList.remove(pMonster);
	delete pMonster;
}

void ObjectManager::CreateProps(int id, Vector pos, Vector size, float angle)
{
	NEW_OBJECT(Object* props, Prop(id));
	props->SetPosition(pos);
	props->SetCollider(size, angle);
	m_propsList.push_back(props);
}

void ObjectManager::DestroyProps(Object* pProps)
{
	m_propsList.remove(pProps);
	DELETE_OBJECT(pProps);
}

void ObjectManager::DestroyAllProps()
{
	FOR_LIST(Object*, m_propsList)
	{
		DELETE_OBJECT((*it));
	}
	m_propsList.clear();
}

void ObjectManager::Update(float deltaTime)
{
	FOR_LIST(Object*, m_propsList)
	{
		(*it)->Update(deltaTime);
	}

	FOR_LIST(Object*, m_monsterList)
	{
		(*it)->Update(deltaTime);
	}

	m_pPlayer->Update(deltaTime);

	FOR_LIST(Object*, m_skillList)
	{
		(*it)->Update(deltaTime);
	}

}

void ObjectManager::Draw(Camera* pCamera)
{
	FOR_LIST(Object*, m_propsList)
	{
		(*it)->Draw(pCamera);
	}

	FOR_LIST(Object*, m_monsterList)
	{
		(*it)->Draw(pCamera);
	}

	FOR_LIST(Object*, m_skillList)
	{
		(*it)->Draw(pCamera);
	}

	m_pPlayer->Draw(pCamera);	
}

void ObjectManager::CreateSkill(Object* pCharacter, SKILL_USER id, SKILL_LIST name)
{
	NEW_OBJECT(Object* skill, Skill(pCharacter, id, name));
	skill->SetPosition(pCharacter->Position());

	skill->Animation()->Register(FIRE_BOLT, new Animation(TEXT("Fire_Bolt"), 11, 60, true, 0.5f));
	

	m_skillList.push_back(skill);

}
void ObjectManager::DestroySkill(Object* pSkill)
{
	m_skillList.remove(pSkill);
	delete pSkill;
}

void ObjectManager::DestroyCompletedSkill()
{
	list<Object*> skillList = OBJECT->GetSkillList();

	FOR_LIST(Object*, skillList)
	{
		if ((*it)->GetIsComplete()==true)
		{
			delete (*it)->GetMagic();
			OBJECT->DestroySkill((*it));
		}
	}
}

void ObjectManager::DestroyAllSkill()
{
	FOR_LIST(Object*, m_skillList)
	{
		delete (*it)->GetMagic();
		DELETE_OBJECT((*it));
	}
	m_skillList.clear();
}