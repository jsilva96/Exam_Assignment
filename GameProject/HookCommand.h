#pragma once
#include <Command.h>
class HookCommand :
	public Command
{
public:
	HookCommand();
	virtual ~HookCommand();

	void Execute() override;

	HookCommand(const HookCommand&) = delete;
	HookCommand(HookCommand&&) noexcept = delete;

	HookCommand& operator=(const HookCommand&) = delete;
	HookCommand& operator=(HookCommand&&) noexcept = delete;
};

