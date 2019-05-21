#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

enum class PlayerState
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

	PlayerSpriteSwitchComponent(const PlayerSpriteSwitchComponent&) = delete;
	PlayerSpriteSwitchComponent(PlayerSpriteSwitchComponent&&) noexcept = delete;

	PlayerSpriteSwitchComponent& operator=(const PlayerSpriteSwitchComponent&) = delete;
	PlayerSpriteSwitchComponent& operator=(PlayerSpriteSwitchComponent&&) noexcept = delete;
private:
	TranslationComponent* m_pTrans;
	SpriteComponent* m_Sprite;
	SpriteDescSwitchComponent* m_Switch;
	float m_DugTimer;

	void SetSpriteIndex(PlayerState s);

	Vector2f m_Dir;
	bool m_IsDigging;
};

