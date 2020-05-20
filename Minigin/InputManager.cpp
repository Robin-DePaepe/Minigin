#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>



InputManager::InputManager()
	:m_pCurrKeyboardState{ nullptr }
	, m_pOldKeyboardState{ nullptr }
	, m_KeyboardState0Active{ true }
{}

InputManager::~InputManager()
{
	delete[] 	m_pKeyboardState0;
	delete[] 	m_pKeyboardState1;

	m_pCurrKeyboardState = nullptr;
	m_pOldKeyboardState = nullptr;
	m_pKeyboardState0 = nullptr;
	m_pKeyboardState1 = nullptr;
}

void InputManager::Initialize(SDL_Window* sdlwindow)
{
	m_pKeyboardState0 = new SHORT[256];
	m_pKeyboardState1 = new SHORT[256];

	GetActualKeyboardState(m_pKeyboardState0);
	GetActualKeyboardState(m_pKeyboardState1);

	m_pSdlWindow = sdlwindow;
}

bool InputManager::ControllerConnected() const
{
	DWORD dwResult;
	XINPUT_STATE controllerState;

	//get controller state
	dwResult = XInputGetState(0, &controllerState);

	//check if controller is connected
	return dwResult == ERROR_SUCCESS;
}

void InputManager::GetMousePos(int& x, int& y) const
{
	POINT point;
	GetCursorPos(&point);
	SDL_GetWindowPosition(m_pSdlWindow, &x, &y);

	x = point.x - x;
	y = point.y - y;
}

void InputManager::ProcessInput()
{
#pragma region
	DWORD dwResult;
	XINPUT_STATE controllerState;

	//get controller state
	dwResult = XInputGetState(0, &controllerState);

	m_PressedButtons.clear();
	m_ReleasedButtons.clear();

	//check if controller is connected
	if (dwResult == ERROR_SUCCESS)
	{
		//check if a button was pressed
		PXINPUT_KEYSTROKE pKeystroke{ new XINPUT_KEYSTROKE{} };

		XInputGetKeystroke(0, 0, pKeystroke);

		//pressed
		if (pKeystroke->Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			XINPUT_GAMEPAD* pGamePad = &controllerState.Gamepad;

			if (pGamePad->wButtons & XINPUT_GAMEPAD_A) ProcessButton(ControllerButton::ButtonA, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_B) ProcessButton(ControllerButton::ButtonB, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_X) ProcessButton(ControllerButton::ButtonX, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_Y) ProcessButton(ControllerButton::ButtonY, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ProcessButton(ControllerButton::RightShoulder, InputTriggerState::Pressed);
			if (pGamePad->bRightTrigger > 10) ProcessButton(ControllerButton::RightTrigger, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ProcessButton(ControllerButton::LeftShoulder, InputTriggerState::Pressed);
			if (pGamePad->bLeftTrigger > 10) ProcessButton(ControllerButton::LeftTrigger, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ProcessButton(ControllerButton::LeftStickClick, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ProcessButton(ControllerButton::RightStickClick, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ProcessButton(ControllerButton::DpadDown, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ProcessButton(ControllerButton::DpadLeft, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ProcessButton(ControllerButton::DpadRight, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP) ProcessButton(ControllerButton::DpadUp, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_START) ProcessButton(ControllerButton::Start, InputTriggerState::Pressed);
			if (pGamePad->wButtons & XINPUT_GAMEPAD_BACK) ProcessButton(ControllerButton::Back, InputTriggerState::Pressed);
		}
		//released
		if (pKeystroke->Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			XINPUT_GAMEPAD* pGamePad = &controllerState.Gamepad;

			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_A)) ProcessButton(ControllerButton::ButtonA, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_B)) ProcessButton(ControllerButton::ButtonB, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_X)) ProcessButton(ControllerButton::ButtonX, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_Y)) ProcessButton(ControllerButton::ButtonY, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) ProcessButton(ControllerButton::RightShoulder, InputTriggerState::Released);
			if (!(pGamePad->bRightTrigger > 10)) ProcessButton(ControllerButton::RightTrigger, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) ProcessButton(ControllerButton::LeftShoulder, InputTriggerState::Released);
			if (!(pGamePad->bLeftTrigger > 10)) ProcessButton(ControllerButton::LeftTrigger, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) ProcessButton(ControllerButton::LeftStickClick, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) ProcessButton(ControllerButton::RightStickClick, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) ProcessButton(ControllerButton::DpadDown, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) ProcessButton(ControllerButton::DpadLeft, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) ProcessButton(ControllerButton::DpadRight, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP)) ProcessButton(ControllerButton::DpadUp, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_START)) ProcessButton(ControllerButton::Start, InputTriggerState::Released);
			if (!(pGamePad->wButtons & XINPUT_GAMEPAD_BACK)) ProcessButton(ControllerButton::Back, InputTriggerState::Released);
		}
		//down
		for (const ControllerButton& button : m_DownButtons)
		{
			ProcessButton(button, InputTriggerState::Down);
		}
		delete pKeystroke;
	}

#pragma endregion controller input

#pragma region

	//update the keyboardStates
	if (m_KeyboardState0Active)
	{
		GetActualKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		GetActualKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

	//look if any of the actions is activated 
	// Iterate over the map using Iterator till end.
	auto it = m_Actions.begin();

	while (it != m_Actions.end())
	{
		if (it->KeyCode == -1) return;

		switch (it->TriggerState)
		{
		case InputTriggerState::Pressed:
			if (IsPressed(it->KeyCode)) it->upCommand->Execute();
			break;
		case InputTriggerState::Released:
			if (IsReleased(it->KeyCode)) it->upCommand->Execute();
			break;
		case InputTriggerState::Down:
			if (IsDown(it->KeyCode)) it->upCommand->Execute();
			break;
		}
		++it;
	}
#pragma endregion keyboard & mouse input
}

bool InputManager::IsDown(ControllerButton button) const
{
	return std::find(m_DownButtons.cbegin(), m_DownButtons.cend(), button) != m_DownButtons.cend();
}

bool InputManager::IsPressed(ControllerButton button) const
{
	return std::find(m_PressedButtons.cbegin(), m_PressedButtons.cend(), button) != m_PressedButtons.cend();
}

bool InputManager::IsReleased(ControllerButton button) const
{
	return std::find(m_ReleasedButtons.cbegin(), m_ReleasedButtons.cend(), button) != m_ReleasedButtons.cend();
}

bool InputManager::IsDown(int virtualKey) const
{
	return	m_pOldKeyboardState[virtualKey] && m_pCurrKeyboardState[virtualKey];//previous state and current one is active
}

bool InputManager::IsPressed(int virtualKey) const
{
	return	!m_pOldKeyboardState[virtualKey] && m_pCurrKeyboardState[virtualKey];//previous state is inactive and current one is active
}

bool InputManager::IsReleased(int virtualKey) const
{
	return	m_pOldKeyboardState[virtualKey] && !m_pCurrKeyboardState[virtualKey];//previous state is active and current one is inactive
}

void InputManager::AddInput(InputAction inputAction)
{
	m_Actions.push_back(inputAction);
}

void InputManager::ProcessButton(ControllerButton button, InputTriggerState triggerState)
{
	//add the button to the correct vector 
	switch (triggerState)
	{
	case InputTriggerState::Pressed:
		m_PressedButtons.push_back(button);
		m_DownButtons.push_back(button);
		break;
	case InputTriggerState::Released:
		auto it = std::find(m_DownButtons.cbegin(), m_DownButtons.cend(), button);

		if (it == m_DownButtons.cend()) return;//button was never pressed

		m_DownButtons.erase(it);
		m_ReleasedButtons.push_back(button);
		break;
	}

	for (const InputAction& action : m_Actions)
	{
		//check if the action matches 
		if (action.ControllerInput == button && action.TriggerState == triggerState)
		{
			action.upCommand->Execute();
		}
	}
}

void InputManager::GetActualKeyboardState(SHORT* state)
{
	for (size_t i = 0; i < 256; i++)state[i] = GetAsyncKeyState(i);
}






