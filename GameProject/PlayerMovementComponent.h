#pragma once
#include <BaseComponent.h>

class InputComponent;
class TranslationComponent;
class PlayerMovementComponent final : public BaseComponent
{
public:
	PlayerMovementComponent(float speed, int plyrNr);
	virtual ~PlayerMovementComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetInputComponent(InputComponent* pInputComponent);
	void SetTranslationComponent(TranslationComponent* pTrans);

	PlayerMovementComponent(const PlayerMovementComponent&) = delete;
	PlayerMovementComponent(PlayerMovementComponent&&) noexcept = delete;

	PlayerMovementComponent& operator=(const PlayerMovementComponent&) = delete;
	PlayerMovementComponent& operator=(PlayerMovementComponent&&) noexcept = delete;

private:
	InputComponent* m_pInput;
	TranslationComponent* m_pTrans;
	float m_Speed;

	int m_PlyrNr;
};

