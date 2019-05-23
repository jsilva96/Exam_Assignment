#include "pch.h"
#include "SelectCommand.h"
#include "EventsAndTags.h"
#include "SomeStructs.h"

#include "SelectionComponent.h"
#include "Time.h"

SelectCommand::SelectCommand(bool moveDown)
	:Command(EVENT::SELECTING), m_MoveDown(moveDown)
{
}
void SelectCommand::Execute()
{
	if ((Time::GetInstance().GetElapsedTime() - m_LastCheck) <= m_MinTime) return;
	auto it = std::find_if(m_Options.begin(), m_Options.end(), [](SelectionComponent* pComp)
	{
		return pComp->IsSelected();
	});

	if (it == m_Options.end()) throw std::runtime_error("SelectCommand::Execute->No option is selected\n");

	(*it)->SetSelected(false);

	if (m_MoveDown)
	{
		if (++it == m_Options.end()) (*m_Options.begin())->SetSelected(true);
		else (*it)->SetSelected(true);
	}
	else
	{
		if (it == m_Options.begin()) (*(m_Options.end() - 1))->SetSelected(true);
		else (*(--it))->SetSelected(true);
	}

	m_LastCheck = Time::GetInstance().GetElapsedTime();
}
void SelectCommand::AddOption(SelectionComponent* pComp)
{
	AddCheck(m_Options, pComp);
}
