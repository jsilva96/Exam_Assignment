#pragma once
#include "EnemySpriteSwitchComponent.h"

enum class FygarState :unsigned int
{
	FIRE = 7
};

class FygarSpriteSwitchComponent final: public EnemySpriteSwitchComponent
{
public:
	FygarSpriteSwitchComponent() = default;
	virtual ~FygarSpriteSwitchComponent() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	FygarSpriteSwitchComponent(const FygarSpriteSwitchComponent&) = delete;
	FygarSpriteSwitchComponent(FygarSpriteSwitchComponent&&) noexcept = delete;

	FygarSpriteSwitchComponent& operator=(const FygarSpriteSwitchComponent&) = delete;
	FygarSpriteSwitchComponent& operator=(FygarSpriteSwitchComponent&&) noexcept = delete;
};

