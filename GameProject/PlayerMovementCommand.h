#pragma once
#include "Command.h"
#include "SomeStructs.h"

class TranslationComponent;
class PlayerMovementCommand final: public Command
{
public:
	PlayerMovementCommand();
	virtual ~PlayerMovementCommand() = default;

	void SetDirection(const Vector2f& v);
	void SetSpeed(float f);
	void Execute() override;

	void SetTranslationComponent(TranslationComponent* pComp);

	PlayerMovementCommand(const PlayerMovementCommand&) = delete;
	PlayerMovementCommand(PlayerMovementCommand&&) noexcept = delete;

	PlayerMovementCommand& operator=(const PlayerMovementCommand&) = delete;
	PlayerMovementCommand& operator=(PlayerMovementCommand&&) noexcept = delete;

private:
	Vector2f m_Dir;
	float m_Speed;

	TranslationComponent* m_TransComponent;
};

