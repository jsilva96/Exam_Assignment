#pragma once
#include "BaseObject.h"
#include <Xinput.h>

class InputComponent;
class Gamepad final : public BaseObject
{
	struct Analog
	{
		float x, y;

		Analog(float x, float y)
			:x(x), y(y)
		{
		}
		Analog()
			:Analog(0.0f, 0.0f)
		{
		}

		bool IsPressed() const { return (x != 0.0f) || (y != 0.0f); }
	};

	//struct LeftAnalog : public Analog
	//{
	//};
	//struct RightAnalog : public Analog
	//{
	//};


public:
	explicit Gamepad(int portNr);
	virtual ~Gamepad();

	void CheckController();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	bool IsPressed(WORD button) const;

	void UpdateValues();

	bool IsConnected() const;
	bool IsAssigned() const;

	float GetLeftTrigger() const;
	float GetRightTrigger() const;

	Vector2f GetLeftAnalogStick() const;
	Vector2f GetRightAnalogStick() const;

	void SetLeftAnalogDeadZone(const Point2f& p);
	void SetRightAnalogDeadZone(const Point2f& p);

	int GetPortNr() const;
private:	
	XINPUT_STATE m_State;
	InputComponent* m_pInput;

	int m_Port;

	bool m_IsConnected;

	float m_LeftTriggerPress;
	float m_RightTriggerPress;

	Point2f m_LeftAnalogDeadZone;
	Point2f m_RightAnalogDeadZone;

	Analog m_LeftAnalog, m_RightAnalog;

	void DoDeadZoneCalculations(Analog& a, const Point2f& p);
	void UpdateAnalogs();

	friend class InputComponent;
	void AssignInput(InputComponent* pComp);
	void UnbindInput();
	
	Gamepad(const Gamepad&) = delete;
	Gamepad(const Gamepad&&) noexcept = delete;

	Gamepad& operator=(const Gamepad&) = delete;
	Gamepad& operator=(const Gamepad&&) noexcept = delete;
};

