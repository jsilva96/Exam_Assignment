#pragma once
#include "Command.h"
#include "SomeStructs.h"

class TranslationComponent;
class PlayerMovementCommand : public Command
{
public:
	PlayerMovementCommand(const std::string& s);
	virtual ~PlayerMovementCommand() = default;

	void SetSpeed(float f);
	void Execute() override;

	void SetTranslationComponent(TranslationComponent* pComp);

	PlayerMovementCommand(const PlayerMovementCommand&) = delete;
	PlayerMovementCommand(PlayerMovementCommand&&) noexcept = delete;

	PlayerMovementCommand& operator=(const PlayerMovementCommand&) = delete;
	PlayerMovementCommand& operator=(PlayerMovementCommand&&) noexcept = delete;
protected:
	void SetDirection(const Vector2f& v);

private:
	Vector2f m_Dir;
	float m_Speed;

	TranslationComponent* m_TransComponent;
};

