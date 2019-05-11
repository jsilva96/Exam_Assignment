#pragma once
#include "BaseComponent.h"
#include <map>

enum class CollisionGroup
{
	Group0 = 0,
	Group1 = 1,
	Group2 = 2,
	Group3 = 3,
	Group4 = 4,
	Group5 = 5,
	Group6 = 6,
	Group7 = 7,
	Group8 = 8,
	Group9 = 9,

};

class GameObject;
class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(const Rectf& rect);
	ColliderComponent();

	virtual ~ColliderComponent();

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Reset() override;

	void SetCollisionGroup(CollisionGroup group, bool b = true);

	virtual void HandleCollision(ColliderComponent* pComp) 
	{
		m_pGameObject->OnCollide(pComp->m_pGameObject);
	};

	Rectf GetRectf() const;
	void SetRectf(const Rectf& rect)
	{
		m_Rect = rect;
	}
	void SetStatic(bool b)
	{
		m_IsStatic = b;
	}

	std::vector<CollisionGroup> GetCollisionGroups() const;
private:
	Rectf m_Rect;
	std::map<CollisionGroup, bool> m_CollisionGroup;
	bool m_IsStatic;

	friend class CollisionManager;
	bool IsStatic() const { return m_IsStatic; }

	ColliderComponent(const ColliderComponent& obj) = delete;
	ColliderComponent(const ColliderComponent&& obj) = delete;

	ColliderComponent& operator=(const ColliderComponent& obj) = delete;
	ColliderComponent& operator=(const ColliderComponent&& obj) = delete;
};