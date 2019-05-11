#pragma once
#include "ColliderComponent.h"
#include "SomeStructs.h"
#include "GameObject.h"

class LevelColliderComponent : public ColliderComponent
{
public:
	LevelColliderComponent();
	virtual ~LevelColliderComponent();

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Reset() override;

	void AddVerts(const std::vector<Point2f>& verts);
	const std::vector<std::vector<Point2f>>& GetVerts() const;

	void OnLevelCollide(HitInfo info, ColliderComponent* pCollider)
	{
		pCollider->GetGameObject()->OnLevelCollide(info);
	}
private:

	std::vector<std::vector<Point2f>> m_Verts;

	LevelColliderComponent(const LevelColliderComponent& obj) = delete;
	LevelColliderComponent(const LevelColliderComponent&& obj) = delete;

	LevelColliderComponent& operator=(const LevelColliderComponent& obj) = delete;
	LevelColliderComponent& operator=(const LevelColliderComponent&& obj) = delete;

};

