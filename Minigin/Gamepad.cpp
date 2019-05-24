#include "MiniginPCH.h"
#include "Gamepad.h"
#include "InputComponent.h"


Gamepad::Gamepad(int portNr)
	:m_Port{ portNr },
	m_LeftAnalogDeadZone{ 0.05f, 0.05f },
	m_RightAnalogDeadZone{ 0.05f, 0.05f },
	m_pInput(nullptr)
{
}
Gamepad::~Gamepad()
{
	m_pInput = nullptr;

	m_LeftTriggerPress = 0.0f;
	m_LeftTriggerPress = 0.0f;

	m_LeftAnalogDeadZone = { 0.05f, 0.05f };
	m_RightAnalogDeadZone = { 0.05f, 0.05f };
}
void Gamepad::CheckController()
{

	/*for (DWORD i = m_ControlNr; i < XUSER_MAX_COUNT && m_Port == -1; i++)
	{
		ZeroMemory(&m_State, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &m_State) == ERROR_SUCCESS)
		{
			++m_ControlNr;
			m_Port = i;
		}
	}
	m_IsConnected = m_Port != -1;

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
	}*/

	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	m_IsConnected = (XInputGetState(m_Port, &m_State) == ERROR_SUCCESS);

	if (m_IsConnected && m_pInput) UpdateValues();
	else
	{
		m_LeftTriggerPress = 0.0f;
		m_RightTriggerPress = 0.0f;

		m_LeftAnalog = { 0.0f, 0.0f };
		m_RightAnalog = { 0.0f, 0.0f };
	}
}

void* Gamepad::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<Gamepad>();
}
void Gamepad::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<Gamepad>(ptrDelete);
}

void Gamepad::AssignInput(InputComponent * pComp)
{
	m_pInput = pComp;
}

void Gamepad::UnbindInput()
{
	if (m_pInput)m_pInput->UnbindGamepad();
	m_pInput = nullptr;
}

bool Gamepad::IsPressed(WORD button) const
{
	if (button == XINPUT_GAMEPAD_LEFT_THUMB) return (m_LeftAnalog.IsPressed()) || (m_State.Gamepad.wButtons & button);
	if (button == XINPUT_GAMEPAD_RIGHT_THUMB) return(m_RightAnalog.IsPressed()) || (m_State.Gamepad.wButtons & button);

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

bool Gamepad::IsAssigned() const
{
	return m_IsConnected && m_pInput;
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
	return Vector2f(m_LeftAnalog.x, m_LeftAnalog.y);
}
Vector2f Gamepad::GetRightAnalogStick() const
{
	return Vector2f(m_RightAnalog.x, m_RightAnalog.y);
}
void Gamepad::SetLeftAnalogDeadZone(const Point2f& p)
{
	m_LeftAnalogDeadZone = p;
}
void Gamepad::SetRightAnalogDeadZone(const Point2f& p)
{
	m_RightAnalogDeadZone = p;
}

int Gamepad::GetPortNr() const
{
	return m_Port;
}
