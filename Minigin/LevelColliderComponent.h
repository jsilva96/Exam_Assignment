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

	void AddVerts(const std::vector<Point2f>& verts);
	const std::vector<std::vector<Point2f>>& GetVerts() const;

	void OnLevelCollide(HitInfo, ColliderComponent*)
	{
		//pCollider->GetGameObject()->OnLevelCollide(info);
	}
private:

	std::vector<std::vector<Point2f>> m_Verts;

	LevelColliderComponent(const LevelColliderComponent&) = delete;
	LevelColliderComponent(LevelColliderComponent&&) noexcept = delete;

	LevelColliderComponent& operator=(const LevelColliderComponent&) = delete;
	LevelColliderComponent& operator=(LevelColliderComponent&&) noexcept = delete;

};

