#include "MiniginPCH.h"
#include "Time.h"

Time* Time::m_Instance = nullptr;
Time::Time()
	:m_ElapsedSecs{},
	m_ElapsedTime{},
	m_NrOfFrames{},
	m_FPS{}
{
}
Time::~Time()
{
}
Time& Time::GetInstance()
{
	if (!m_Instance) m_Instance = new Time();
	
	return *m_Instance;
}
void Time::DestroyInstance()
{
	if (m_Instance) delete m_Instance;
}
void Time::Update(float elapsedSecs)
{
	m_ElapsedSecs = elapsedSecs;

	m_ElapsedTime += m_ElapsedSecs;

	++m_NrOfFrames;

	m_FPS = int(m_NrOfFrames / m_ElapsedTime);
}
const float Time::GetElapsedSecs() const
{
	return m_ElapsedSecs;
}
const float Time::GetElapsedTime() const
{
	return m_ElapsedTime;
}
const int Time::GetFPS() const
{
	return m_FPS;
}