#pragma once
#include <BaseComponent.h>

enum class EnemyState :unsigned int
{
	MOVING = 0,
	PHASING,
	CRUSHED,
	HOOKED_1,
	HOOKED_2,
	HOOKED_3,
	HOOKED_4,
};
 
class SpriteDirectionComponent;
class TranslationComponent;
class SpriteComponent;
class SpriteDescSwitchComponent;
class TimerComponent;
class EnemySpriteSwitchComponent : public BaseComponent
{
public:
	EnemySpriteSwitchComponent() = default;
	virtual ~EnemySpriteSwitchComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Pump();

	void SetTranslationComponent(TranslationComponent* pComp);
	void SetSpriteComponent(SpriteComponent* pComp);

	void SetSpriteIndex(int index);

	bool IsEnemyDead() const
	{
		if (m_State == (unsigned int)EnemyState::CRUSHED) return true;
		if (m_State == (unsigned int)EnemyState::HOOKED_4) return true;

		return false;
	}

	EnemySpriteSwitchComponent(const EnemySpriteSwitchComponent&) = delete;
	EnemySpriteSwitchComponent(EnemySpriteSwitchComponent&&) noexcept = delete;

	EnemySpriteSwitchComponent& operator=(const EnemySpriteSwitchComponent&) = delete;
	EnemySpriteSwitchComponent& operator=(EnemySpriteSwitchComponent&&) noexcept = delete;

protected:
	TimerComponent* m_pTimer = nullptr;
	SpriteDescSwitchComponent* m_Switch = nullptr;
	unsigned int m_State = 0;

private:
	SpriteDirectionComponent* m_SpriteDir = nullptr;
	TranslationComponent* m_pTrans = nullptr;
	SpriteComponent* m_Sprite = nullptr;
};

