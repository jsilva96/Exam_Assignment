#include "MiniginPCH.h"
#include "TimerComponent.h"
#include "Time.h"


TimerComponent::TimerComponent()
	:m_State{ TimerState::RUNNING },
	 m_Timer{},
	 m_StartTimer{}
{
}
TimerComponent::~TimerComponent()
{
}
void TimerComponent::Initialize()
{
}
void TimerComponent::Update()
{
	if (m_State != TimerState::RUNNING) return;

	m_Timer -= Time::GetInstance().GetElapsedSecs();

	if (m_Timer <= 0.0f) m_State = TimerState::ENDED;
}
void TimerComponent::Render() const
{
}
void TimerComponent::Reset()
{
	BaseComponent::Reset();

	m_State = TimerComponent::RUNNING;
	m_Timer = 0.0f;
}
void TimerComponent::SetTimer(float inSeconds)
{
	m_StartTimer = inSeconds;
	m_Timer = inSeconds;
}
void TimerComponent::PauseTimer()
{
	if (m_State != TimerState::ENDED) m_State = TimerState::PAUSED;
}
void TimerComponent::StartTimer()
{
	if (m_State != TimerState::ENDED) m_State = TimerState::RUNNING;
}
bool TimerComponent::IsTimerOver() const
{
	return m_State == TimerState::ENDED;
}
float TimerComponent::GetRemainingTimer() const
{
	return m_Timer;
}
void TimerComponent::RestartTimer()
{
	m_Timer = m_StartTimer;
	m_State = TimerState::RUNNING;
}
