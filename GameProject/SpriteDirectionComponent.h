#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

class TranslationComponent;
class SpriteComponent;

class SpriteDirectionComponent final: public BaseComponent
{
public:
	SpriteDirectionComponent() = default;
	virtual ~SpriteDirectionComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetTranslationComponent(TranslationComponent* pComp);
	void SetSpriteComponent(SpriteComponent* pComp);

	SpriteDirectionComponent(const SpriteDirectionComponent&) = delete;
	SpriteDirectionComponent(SpriteDirectionComponent&&) noexcept = delete;

	SpriteDirectionComponent& operator=(const SpriteDirectionComponent&) = delete;
	SpriteDirectionComponent& operator=(SpriteDirectionComponent&&) noexcept = delete;

private:
	Vector2f m_Dir;

	TranslationComponent* m_pTrans = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

