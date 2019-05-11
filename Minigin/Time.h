#pragma once

class Time
{
public:

	static Time& GetInstance();
	void DestroyInstance();

	void Update(float elapsedSecs);
	const float GetElapsedSecs() const;
	const float GetElapsedTime() const;
	const int GetFPS() const;


private:
	Time();
	~Time();

	Time(const Time& obj) = delete;
	Time(Time&& obj) = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& other) = delete;


	static Time* m_Instance;
	float m_ElapsedSecs;
	int m_NrOfFrames;
	float m_ElapsedTime;
	int m_FPS;
};

