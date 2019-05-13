#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

class EnemyManager : public BaseComponent
{
public:
	EnemyManager() = default;
	virtual ~EnemyManager() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override {};
	void Update() override {};
	void Render() const override {};

	GameObject* GetFygar(const Point2f& pos, float scale) const;
	GameObject* GetPooka(const Point2f& pos, float scale) const;

	EnemyManager(const EnemyManager& obj) = delete;
	EnemyManager(EnemyManager&& obj) noexcept = delete;

	EnemyManager& operator=(const EnemyManager& obj) = delete;
	EnemyManager& operator=(EnemyManager&& obj) noexcept = delete;
};

