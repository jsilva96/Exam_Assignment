#pragma once
#include "BaseObject.h"
#include <Xinput.h>

class InputComponent;
class Gamepad : public BaseObject
{
	struct Analog  :  public Vector2f
	{
	};

	struct LeftAnalog : public Analog
	{
	};
	struct RightAnalog : public Analog
	{
	};


public:
	Gamepad();
	virtual ~Gamepad();

	void Reset() override;

	void CheckController();

	bool IsPressed(WORD button) const;

	void UpdateValues();

	bool IsConnected() const;

	float GetLeftTrigger() const;
	float GetRightTrigger() const;

	Vector2f GetLeftAnalogStick() const;
	Vector2f GetRightAnalogStick() const;

	void SetLeftAnalogDeadZone(const Point2f& p);
	void SetRightAnalogDeadZone(const Point2f& p);

private:	
	XINPUT_STATE m_State;
	InputComponent* m_pInput;

	int m_Port;

	bool m_IsConnected;

	static int m_ControlNr;

	float m_LeftTriggerPress;
	float m_RightTriggerPress;

	Point2f m_LeftAnalogDeadZone;
	Point2f m_RightAnalogDeadZone;

	LeftAnalog m_LeftAnalog;
	RightAnalog m_RightAnalog;

	void DoDeadZoneCalculations(Analog& a, const Point2f& p);
	void UpdateAnalogs();

	friend class InputComponent;
	void AssignInput(InputComponent* pComp);
	
	Gamepad(const Gamepad&) = delete;
	Gamepad(const Gamepad&&) = delete;

	Gamepad& operator=(const Gamepad&) = delete;
	Gamepad& operator=(const Gamepad&&) = delete;
};

