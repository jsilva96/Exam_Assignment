#pragma once
#include <Command.h>
class SelectionComponent;
class SelectCommand final: public Command
{
public:
	SelectCommand();
	virtual ~SelectCommand() = default;

	void Execute() override;

	void AddOption(SelectionComponent* pComp);

	SelectCommand(const SelectCommand&) = delete;
	SelectCommand(SelectCommand&&) noexcept = delete;

	SelectCommand& operator=(const SelectCommand&) = delete;
	SelectCommand& operator=(SelectCommand&&) noexcept = delete;

private:
	std::vector<SelectionComponent*> m_Options;

	float m_LastCheck = 0.0f;
	float m_MinTime = 0.1f;
};

