#include "MiniginPCH.h"
#include "Gamepad.h"
#include "InputComponent.h"

int Gamepad::m_ControlNr = 0;

Gamepad::Gamepad()
	:m_Port{ -1 },
	m_LeftAnalogDeadZone{ 0.05f, 0.05f },
	m_RightAnalogDeadZone{ 0.05f, 0.05f }
{
}
Gamepad::~Gamepad()
{
}
void Gamepad::Reset()
{
	m_pInput = nullptr;

	m_LeftTriggerPress = 0.0f;
	m_LeftTriggerPress = 0.0f;

	m_LeftAnalogDeadZone = { 0.05f, 0.05f };
	m_RightAnalogDeadZone = { 0.05f, 0.05f };
}
void Gamepad::CheckController()
{
	if (m_Port == -1)
	{
		for (DWORD i = m_ControlNr; i < XUSER_MAX_COUNT && m_Port == -1; i++)
		{
			ZeroMemory(&m_State, sizeof(XINPUT_STATE));

			if (XInputGetState(i, &m_State) == ERROR_SUCCESS)
			{
				++m_ControlNr;
				m_Port = i;
			}
		}
		m_IsConnected = m_Port != -1;
	}

	if (m_IsConnected)
	{
		if (XInputGetState(m_Port, &m_State) != ERROR_SUCCESS)
		{
			--m_ControlNr;
			m_Port = -1;

			m_LeftTriggerPress = 0.0f;
			m_LeftTriggerPress = 0.0f;

			m_LeftAnalogDeadZone = { 0.05f, 0.05f };
			m_RightAnalogDeadZone = { 0.05f, 0.05f };
		}
		else UpdateValues();
	}
}
void Gamepad::AssignInput(InputComponent * pComp)
{
	m_pInput = pComp;
}
bool Gamepad::IsPressed(WORD button) const
{
	if (button == XINPUT_GAMEPAD_LEFT_THUMB) return (m_LeftAnalog != Vector2f{ 0.0f, 0.0f }) || (m_State.Gamepad.wButtons & button);
	if (button == XINPUT_GAMEPAD_RIGHT_THUMB) return(m_RightAnalog != Vector2f{ 0.0f, 0.0f }) || (m_State.Gamepad.wButtons & button);
	
	return m_State.Gamepad.wButtons & button;
}
void Gamepad::UpdateValues()
{
	m_LeftTriggerPress = float(m_State.Gamepad.bLeftTrigger / 255);
	m_RightTriggerPress = float(m_State.Gamepad.bRightTrigger / 255);

	UpdateAnalogs();
}
void Gamepad::UpdateAnalogs()
{
	m_LeftAnalog.x = fmaxf(-1.0f, float(m_State.Gamepad.sThumbLX / 32767.0f));
	m_LeftAnalog.y = fmaxf(-1.0f, float(m_State.Gamepad.sThumbLY / 32767.0f));

	m_RightAnalog.x = fmaxf(-1.0f, float(m_State.Gamepad.sThumbRX / 32767.0f));
	m_RightAnalog.y = fmaxf(-1.0f, float(m_State.Gamepad.sThumbRY / 32767.0f));

	DoDeadZoneCalculations(m_LeftAnalog, m_LeftAnalogDeadZone);
	DoDeadZoneCalculations(m_RightAnalog, m_RightAnalogDeadZone);
}
void Gamepad::DoDeadZoneCalculations(Analog & a, const Point2f & p)
{
	if (abs(a.x) < p.x) a.x = 0.0f;
	else a.x = (abs(a.x) - p.x) * (a.x / abs(a.x));

	if (abs(a.y) < p.y) a.y = 0.0f;
	else a.y = (abs(a.y) - p.y) * (a.y / abs(a.y));

	if (p.x > 0.0f) a.x /= 1 - p.x;
	if (p.y > 0.0f) a.y /= 1 - p.y;
}
bool Gamepad::IsConnected() const
{
	return m_IsConnected;
}
float Gamepad::GetLeftTrigger() const
{
	return m_LeftTriggerPress;
}
float Gamepad::GetRightTrigger() const
{
	return m_RightTriggerPress;
}
Vector2f Gamepad::GetLeftAnalogStick() const
{
	return m_LeftAnalog;
}
Vector2f Gamepad::GetRightAnalogStick() const
{
	return m_RightAnalog;
}
void Gamepad::SetLeftAnalogDeadZone(const Point2f& p)
{
	m_LeftAnalogDeadZone = p;
}
void Gamepad::SetRightAnalogDeadZone(const Point2f& p)
{
	m_RightAnalogDeadZone = p;
}
