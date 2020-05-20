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

enum class PlayerIndex 
{
	playerOne,	 playerTwo, playerThree, playerFour
};

struct InputAction
{
	InputAction(std::shared_ptr<Command> upCommand,int keyboardCode = -1,ControllerButton controllerButton = ControllerButton::none,
		InputTriggerState triggerState = InputTriggerState::Pressed, PlayerIndex playerIndex = PlayerIndex::playerOne)
		:KeyCode{keyboardCode}
		,ControllerInput{controllerButton}
		,TriggerState{triggerState}
		, PlayerIndex{playerIndex}
		,upCommand{upCommand}
	{}

	int KeyCode;
	ControllerButton ControllerInput;
	std::shared_ptr<Command> upCommand;
	InputTriggerState TriggerState;
	PlayerIndex PlayerIndex;
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

	void AddInput(InputAction inputAction);

	void Initialize(SDL_Window* sdlwindow);
private:
	std::vector<ControllerButton> m_PressedButtons;
	std::vector<ControllerButton> m_ReleasedButtons;
	std::vector<ControllerButton> m_DownButtons;

	std::vector<InputAction> m_Actions;

	 BYTE* m_pCurrKeyboardState, * m_pOldKeyboardState, * m_pKeyboardState0, * m_pKeyboardState1;
	 bool m_KeyboardState0Active;

	 SDL_Window * m_pSdlWindow;
	//functions
	void ProcessButton(ControllerButton button, InputTriggerState triggerState);

};


