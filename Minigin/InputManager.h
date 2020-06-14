#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <unordered_map>
#include "Command.h"

struct SDL_Window;

enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	LeftShoulder,
	LeftTrigger,
	RightTrigger,
	RightShoulder,
	DpadUp,
	DpadDown,
	DpadLeft,
	DpadRight,
	Start,
	Back,
	LeftStickClick,
	RightStickClick,
	none,
};

enum class InputTriggerState
{
	Pressed,	Released,	Down
};


struct InputAction
{
	InputAction(shared_ptr<Command> upCommand,bool active,int keyboardCode = -1,ControllerButton controllerButton = ControllerButton::none,	InputTriggerState triggerState = InputTriggerState::Pressed)
		:KeyCode{keyboardCode}
		,ControllerInput{controllerButton}
		,TriggerState{triggerState}
		,upCommand{upCommand}
		,Active{active}
	{}

	int KeyCode;
	ControllerButton ControllerInput;
	shared_ptr<Command> upCommand;
	InputTriggerState TriggerState;
	bool Active;
};

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	bool ControllerConnected() const;
	void GetMousePos(int& x, int& y) const;

	void ProcessInput();

	bool IsPressed(ControllerButton button) const;
	bool IsPressed(int virtualKey) const;

	bool IsDown(ControllerButton button) const;
	bool IsDown(int virtualKey) const;	
	
	bool IsReleased(ControllerButton button) const;
	bool IsReleased(int virtualKey) const;

	size_t AddInput(InputAction inputAction);
	void ChangeInputActionStatus(size_t id,bool active);

	void Initialize(SDL_Window* sdlwindow);
private:
	vector<ControllerButton> m_PressedButtons;
	vector<ControllerButton> m_ReleasedButtons;
	vector<ControllerButton> m_DownButtons;

	vector<InputAction> m_Actions;

	 SHORT* m_pCurrKeyboardState, * m_pOldKeyboardState, * m_pKeyboardState0, * m_pKeyboardState1;
	 bool m_KeyboardState0Active;

	 SDL_Window * m_pSdlWindow;
	//functions
	void ProcessButton(ControllerButton button, InputTriggerState triggerState);
	void GetActualKeyboardState(SHORT* state);//getkeyboardstate only returned false for every key
};


