#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

enum class PlayerState : int
{
	IDLE,
	MOVING,
	DIGING,
	HOOK,
	HOOKED,
	CRUSHED,
	DEAD
};
class TranslationComponent;
class SpriteComponent;
class SpriteDescSwitchComponent;
class SpriteDirectionComponent;

class PlayerSpriteSwitchComponent final: public BaseComponent
{
public:
	PlayerSpriteSwitchComponent();
	virtual ~PlayerSpriteSwitchComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetTranslationComponent(TranslationComponent* pComp);
	void SetSpriteComponent(SpriteComponent* pComp);

	void IsDigging(bool isDigging);

	void SetSpriteIndex(PlayerState s);

	PlayerSpriteSwitchComponent(const PlayerSpriteSwitchComponent&) = delete;
	PlayerSpriteSwitchComponent(PlayerSpriteSwitchComponent&&) noexcept = delete;

	PlayerSpriteSwitchComponent& operator=(const PlayerSpriteSwitchComponent&) = delete;
	PlayerSpriteSwitchComponent& operator=(PlayerSpriteSwitchComponent&&) noexcept = delete;
private:
	SpriteDirectionComponent* m_SpriteDir = nullptr;
	TranslationComponent* m_pTrans = nullptr;
	SpriteComponent* m_Sprite = nullptr;
	SpriteDescSwitchComponent* m_Switch = nullptr;
	float m_DugTimer;

	Vector2f m_Dir;
	bool m_IsDigging;

	PlayerState m_State;
};

