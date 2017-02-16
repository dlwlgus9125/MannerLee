#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "AnimationController.h"
#include <list>
#include "Common.h"
#include "SoundManager.h"

using namespace std;

#define OBJECT ObjectManager::Instance()

class Object
{
protected:
	AnimationController* m_pAnim;
	int m_id;
	Vector m_pos;
	Vector m_dir;
	Magic* m_Magic;
public:
	Object(int id)
	{
		m_pAnim = new AnimationController();
		m_id = id;
	}

	~Object()
	{
		delete m_pAnim;
	}

	AnimationController* Animation() { return m_pAnim; }
	int ID() { return m_id; }
	Vector Position() { return m_pos; }
	virtual void SetPosition(Vector pos){}

	virtual Box Collider() { Box null; return null; }
	virtual Circle getCircle() { Circle null; return null; }
	virtual void SetCharacterCollider(float radius){ }
	virtual void SetSkillCollider(Vector center, Vector dir,float radius) {}
	virtual void SetCollider(Vector size, float angle) {}
	virtual void SetStandPosition() {}
	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera){ }
	virtual void Hit(float damage) { }
	virtual Vector GetDir() { return m_dir; }
	virtual void SetMonsterKind(MONSTER_KIND kind) {}
	virtual void LoadingMonsterImage() {}
	virtual Magic* GetMagic() { return m_Magic; }
	Object(){}
};

class Prop : public Object
{
	Box m_collider;

public:
	Prop(int id) : Object(id)
	{
	}

	Box Collider() { return m_collider; }

	void SetPosition(Vector pos)
	{
		m_pos = pos;
		m_collider.center = pos;
	}
	
	void SetCollider(Vector size, float angle=0) 
	{
		m_collider.size = size;
		m_collider.SetAngle(angle);
	}

	void Draw(Camera* pCamera) 
	{
		if(this->ID()==OBJ_GROUND)pCamera->DrawRect(m_collider.LeftTop(), Vector(m_collider.size.x, m_collider.size.y), ColorF::Red, 2);
		if (this->ID() == OBJ_HIDE)pCamera->DrawRect(m_collider.LeftTop(), Vector(m_collider.size.x, m_collider.size.y), ColorF::Blue, 2);
	}

};

class ObjectManager : public Singleton<ObjectManager>
{
	Object* m_pPlayer;
	list<Object*> m_propsList;
	list<Object*> m_monsterList;
	list<Object*> m_skillList;

public:
	void CreatePlayer(Vector pos, float colRadius);
	void DestroyPlayer();

	void CreateMonster(int id, MONSTER_KIND kind, Vector pos, float colRadius);
	void DestroyAllMonster();

	void CreateSkill(Object* pCharacter, SKILL_USER id,SKILL_LIST name = SKILL_NONE);
	void DestroySkill(Object* pSkill);
	void DestroyAllSkill();
	
	void CreateProps(int id, Vector pos, Vector size, float angle=0);
	void DestroyProps(Object* pProps);
	void DestroyAllProps();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	Object* GetPlayer() { return m_pPlayer; }

	list<Object*> GetMonsterList() { return m_monsterList; }

	Object* GetProps(int id)
	{
		FOR_LIST(Object*, m_propsList)
		{
			if ((*it)->ID() == id) return (*it);
		}
		return NULL;
	}

	Object* GetSkill(int id)
	{
		FOR_LIST(Object*, m_skillList)
		{
			if ((*it)->ID() == id) return (*it);
		}
		return NULL;
	}

	list<Object*> GetPropsList(int id)
	{
		list<Object*> result;
		FOR_LIST(Object*, m_propsList)
		{
			if ((*it)->ID() == id) result.push_back(*it);
		}
		return result;
	}

	list<Object*> GetSkillList(int id)
	{
		list<Object*> result;
		FOR_LIST(Object*, m_skillList)
		{
			if ((*it)->ID() == id) result.push_back(*it);
		}
		return result;
	}

	list<Object*> GetPropsList() { return m_propsList; }
	list<Object*> GetSkillList() { return m_skillList; }//
};

