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
	
}

void ObjectManager::DestroyPlayer()
{
	DELETE_OBJECT(m_pPlayer);
}

void ObjectManager::CreateMonster(int id, Vector pos, float colRadius)
{
	NEW_OBJECT(Object* monster, Monster(id));
	monster->SetPosition(pos);
	monster->SetCharacterCollider(colRadius);
	monster->SetStandPosition();
	

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

	m_pPlayer->Draw(pCamera);
}

void ObjectManager::CreateSkill(Object* pCharacter,SKILL_LIST id, Vector size)
{
	NEW_OBJECT(Object* skill, Skill(pCharacter,id));

	skill->SetPosition(pCharacter->Position());
	skill->SetSkillCollider(pCharacter->Position(),pCharacter->GetDir(),size);

	m_skillList.push_back(skill);
	
}
void ObjectManager::DestroySkill(Object* pSkill)
{
	m_skillList.remove(pSkill);
	delete pSkill;
}
void ObjectManager::DestroyAllSkill()
{
	FOR_LIST(Object*, m_skillList)
	{
		DELETE_OBJECT((*it));
	}
	m_skillList.clear();
}