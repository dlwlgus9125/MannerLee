#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "AnimationController.h"
#include <list>
#include "Common.h"
using namespace std;

#define OBJECT ObjectManager::Instance()

class Object
{
protected:
	AnimationController* m_pAnim;
	int m_id;
	Vector m_pos;


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
	virtual void SetSkillCollider(Vector center, Vector dir, float lineSIze);
	virtual void SetCollider(Vector colSize, Vector anchor) {}
	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera){ }
	virtual void Hit(float damage) { }
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
		m_collider.leftTop = pos;
	}
	
	void SetCollider(Vector width, Vector height) 
	{
		m_collider.width = width;
		m_collider.height = height;
	}

	void Draw(Camera* pCamera) 
	{
		pCamera->DrawRect(m_pos, Vector(m_collider.width.Magnitude(), m_collider.height.Magnitude()), ColorF::Red, 2);

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

	void CreateMonster(int id, Vector pos, float colRadius);
	void DestroyAllMonster();


	void CreateSkill(int id, Vector pos, float colsize);
	void DestroySkill(int id);
	void DestroyAllSkill();


	void CreateProps(int id, Vector pos, Vector width, Vector height);
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

	list<Object*> GetPropsList(int id)
	{
		list<Object*> result;
		FOR_LIST(Object*, m_propsList)
		{
			if ((*it)->ID() == id) result.push_back(*it);
		}
		return result;
	}

	list<Object*> GetPropsList() { return m_propsList; }
};

