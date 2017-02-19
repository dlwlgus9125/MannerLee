#include "ObjectManager.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Boss.h"
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

	m_pPlayer->Animation()->Register(ATTACK_UP, new Animation(TEXT("Attack_Up"), 2, 2, false, 2.0f));
	m_pPlayer->Animation()->Register(ATTACK_LEFT, new Animation(TEXT("Attack_Left"), 2, 2, false, 2.0f));
	m_pPlayer->Animation()->Register(ATTACK_RIGHT, new Animation(TEXT("Attack_Right"), 2, 2, false, 2.0f));
	m_pPlayer->Animation()->Register(ATTACK_DOWN, new Animation(TEXT("Attack_Down"), 2, 2, false, 2.0f));

	m_pPlayer->Animation()->Register(ATTRIBUTE_NONE, new Animation(TEXT("Attribute_None"), 8, 10, true, 0.5f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_FIRE, new Animation(TEXT("Attribute_Fire"), 8, 10, true, 0.5f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_WATER, new Animation(TEXT("Attribute_Water"), 8, 10, true, 0.5f));
	m_pPlayer->Animation()->Register(ATTRIBUTE_ELECTRICITY, new Animation(TEXT("Attribute_Electricity"), 8, 10, true, 0.5f));

	m_pPlayer->Animation()->Register(RUNE_FIRE, new Animation(TEXT("Rune_Fire"), 7, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(RUNE_ICE, new Animation(TEXT("Rune_Ice"), 7, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(RUNE_ELECTRICITY, new Animation(TEXT("Rune_Electricity"), 7, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(RUNE_BOLT, new Animation(TEXT("Rune_Bolt"), 7, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(RUNE_SHIELD, new Animation(TEXT("Rune_Shield"), 7, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(RUNE_WALL, new Animation(TEXT("Rune_Wall"), 7, 10, true, 0.3f));

	m_pPlayer->Animation()->Register(CORRECT_FIRE, new Animation(TEXT("Correct_Fire"), 1, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(CORRECT_ICE, new Animation(TEXT("Correct_Ice"), 1, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(CORRECT_ELECTRICITY, new Animation(TEXT("Correct_Electricity"), 1, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(CORRECT_BOLT, new Animation(TEXT("Correct_Bolt"), 1, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(CORRECT_SHIELD, new Animation(TEXT("Correct_Shield"), 1, 10, true, 0.3f));
	m_pPlayer->Animation()->Register(CORRECT_WALL, new Animation(TEXT("Correct_Wall"), 1, 10, true, 0.3f));
	
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

	TCHAR Kind[100] = {};
	TCHAR Directory[100] = {};
	
	switch (kind)
	{
	case MONSTER_MINION_RED: wsprintf(Kind, TEXT("FireMinion")); break;
	case MONSTER_MINION_BLUE:wsprintf(Kind, TEXT("WaterMinion")); break;

	}
	wsprintf(Directory, TEXT("%s/Minion_Idle_Up"), Kind);
	monster->Animation()->Register(MINION_IDLE_UP +kind, new Animation(Directory, 1, 10, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Idle_Left"), Kind);
	monster->Animation()->Register(MINION_IDLE_LEFT + kind, new Animation(Directory, 1, 10, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Idle_Right"), Kind);
	monster->Animation()->Register(MINION_IDLE_RIGHT + kind, new Animation(Directory, 1, 10, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Idle_Down"), Kind);
	monster->Animation()->Register(MINION_IDLE_DOWN + kind, new Animation(Directory, 1, 10, true, 2.0f));

	wsprintf(Directory, TEXT("%s/Minion_Run_Up"), Kind);
	monster->Animation()->Register(MINION_RUN_UP + kind, new Animation(Directory, 3, 5, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Run_Left"), Kind);
	monster->Animation()->Register(MINION_RUN_LEFT + kind, new Animation(Directory, 3, 5, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Run_Right"), Kind);
	monster->Animation()->Register(MINION_RUN_RIGHT + kind, new Animation(Directory, 3, 5, true, 2.0f));
	wsprintf(Directory, TEXT("%s/Minion_Run_Down"), Kind);
	monster->Animation()->Register(MINION_RUN_DOWN + kind, new Animation(Directory, 3, 5, true, 2.0f));

	
	
	m_monsterList.push_back(monster);
}

void ObjectManager::CreateBoss(int id, Vector pos, float colRadius)
{
	cout << "TESt1" << endl;
	NEW_OBJECT(Object* m_pBoss, Boss(id));
	m_pBoss->SetPosition(pos);
	m_pBoss->SetCharacterCollider(colRadius);

	m_pBoss->Animation()->Register(BOSS_IDLE, new Animation(TEXT("Boss_Idle"), 13,10 , true, 0.5f));
	m_pBoss->Animation()->Register(BOSS_ATTACK, new Animation(TEXT("Boss_Attack"), 5, 10, true, 0.5f));
	m_pBoss->Animation()->Register(EYE_GREEN, new Animation(TEXT("Eye_Green"), 7, 6, true, 0.5f));
	m_pBoss->Animation()->Register(EYE_BLUE, new Animation(TEXT("Eye_Blue"), 7, 6, true, 0.5f));
	m_pBoss->Animation()->Register(EYE_RED, new Animation(TEXT("Eye_Red"), 7, 6, true, 0.5f));
	m_pBoss->Animation()->Register(EYE_YELLOW, new Animation(TEXT("Eye_Yellow"), 7, 6, true, 0.5f));

	m_monsterList.push_back(m_pBoss);

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
	m_pPlayer->Draw(pCamera);
	FOR_LIST(Object*, m_skillList)
	{
		(*it)->Draw(pCamera);
	}


}

void ObjectManager::CreateSkill(Object* pCharacter, SKILL_USER id, SKILL_LIST name, int gage)
{
	NEW_OBJECT(Object* skill, Skill(pCharacter, id, name));
	skill->SetPosition(pCharacter->Position());

	if (id==USER_PLAYER)
	{
		switch (name)
		{
		case FIRE_BOLT:case WATER_BOLT:case ELECTRICITY_BOLT:SOUND->Play("BoltCast", 2.0f); break;
		case FIRE_SHIELD:case WATER_SHIELD:case ELECTRICITY_SHIELD:SOUND->Play("ShieldCast", 2.0f); break;
		case FIRE_WALL:case WATER_WALL:case ELECTRICITY_WALL:SOUND->Play("WallCast", 2.0f); break;
		}
	}

	skill->Animation()->Register(FIRE_BOLT, new Animation(TEXT("Fire_Bolt"), 11, 60, true, 0.5f));
	skill->Animation()->Register(FIRE_SHIELD, new Animation(TEXT("Fire_Shield"), 8, 20, true, 1.0f));
	skill->Animation()->Register(FIRE_WALL, new Animation(TEXT("Fire_Wall"), 4, 20, true, 0.7f));
	skill->Animation()->Register(FIRE_EXPLOSION, new Animation(TEXT("Fire_Explosion"), 23, 30, false, 1.5f));
	
	skill->Animation()->Register(WATER_BOLT, new Animation(TEXT("Ice_Bolt"), 7, 30, true, 1.0f));
	skill->Animation()->Register(WATER_SHIELD, new Animation(TEXT("Ice_Shield"), 8, 20, true, 1.0f));
	skill->Animation()->Register(WATER_WALL, new Animation(TEXT("Ice_Wall"), 30, 30, true, 0.8f));
	skill->Animation()->Register(WATER_EXPLOSION, new Animation(TEXT("Ice_Explosion"), 11, 10, false, 0.7f));

	skill->Animation()->Register(ELECTRICITY_BOLT, new Animation(TEXT("Electricity_Bolt"), 4, 30, true, 0.6f));
	skill->Animation()->Register(ELECTRICITY_SHIELD, new Animation(TEXT("Electricity_Shield"), 8, 20, true, 1.0f));
	skill->Animation()->Register(ELECTRICITY_WALL, new Animation(TEXT("Electricity_Wall"), 4, 30, true,1.5f));
	skill->Animation()->Register(ELECTRICITY_EXPLOSION, new Animation(TEXT("Electricity_Explosion"), 6, 10, false, 1.0f));

	skill->Animation()->Register(100, new Animation(TEXT("Danger"), 1, 10, true, 10.0f));
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

void ObjectManager::LoadingMonsterImage()
{
	TCHAR Address[200] = {};
	TCHAR Kind[100] = {};
	TCHAR Directory[100] = {};
	for (int i = 1; i < 3; i++)
	{
		if (i == 1)wsprintf(Kind, TEXT("FireMinion")); 
		if (i == 2)wsprintf(Kind, TEXT("WaterMinion")); 



		wsprintf(Address, TEXT("Image/Monster/%s/Idle/Up/Up"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Idle_Up"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 1);
		wsprintf(Address, TEXT("Image/Monster/%s/Idle/Down/Down"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Idle_Down"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 1);
		wsprintf(Address, TEXT("Image/Monster/%s/Idle/Left/Left"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Idle_Left"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 1);
		wsprintf(Address, TEXT("Image/Monster/%s/Idle/Right/Right"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Idle_Right"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 1);


		wsprintf(Address, TEXT("Image/Monster/%s/Run/Up/Up"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Run_Up"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 3);
		wsprintf(Address, TEXT("Image/Monster/%s/Run/Down/Down"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Run_Down"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 3);
		wsprintf(Address, TEXT("Image/Monster/%s/Run/Left/Left"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Run_Left"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 3);
		wsprintf(Address, TEXT("Image/Monster/%s/Run/Right/Right"), Kind);
		wsprintf(Directory, TEXT("%s/Minion_Run_Right"), Kind);
		RENDER->LoadImageFiles(Directory, Address, TEXT("png"), 3);

	}
}