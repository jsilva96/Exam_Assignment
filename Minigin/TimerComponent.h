#pragma once
#include "BaseComponent.h"
class TimerComponent : public BaseComponent
{
	enum TimerState
	{
		RUNNING,
		PAUSED,
		ENDED
	};
public:
	TimerComponent();
	virtual ~TimerComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetTimer(float inSeconds);
	
	void PauseTimer();
	void StartTimer();

	bool IsTimerOver() const;

	float GetRemainingTimer() const;

	void RestartTimer();
private:
	float m_Timer;
	float m_StartTimer;

	TimerState m_State;

	TimerComponent(const TimerComponent&) = delete;
	TimerComponent(const TimerComponent&&) noexcept = delete;

	TimerComponent& operator=(const TimerComponent&) = delete;
	TimerComponent& operator=(const TimerComponent&&) noexcept = delete;
};

