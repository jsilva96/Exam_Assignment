#pragma once
#include <Command.h>
class PlayerSpriteSwitchComponent;
class HookCommand final: public Command
{
public:
	HookCommand();
	virtual ~HookCommand();

	void Execute() override;

	HookCommand(const HookCommand&) = delete;
	HookCommand(HookCommand&&) noexcept = delete;

	HookCommand& operator=(const HookCommand&) = delete;
	HookCommand& operator=(HookCommand&&) noexcept = delete;

private:
	PlayerSpriteSwitchComponent* m_pPlayer = nullptr;
};

