#pragma once
#include <Command.h>
class EnterCommand final : public Command
{
public:
	EnterCommand();
	virtual ~EnterCommand() = default;

	void Execute() override;

	EnterCommand(const EnterCommand&) = delete;
	EnterCommand(EnterCommand&&) noexcept = delete;

	EnterCommand& operator=(const EnterCommand&) = delete;
	EnterCommand& operator=(EnterCommand&&) noexcept = delete;
};

