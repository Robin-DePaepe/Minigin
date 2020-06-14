#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "EngineInput.h"

using namespace chrono;

bool minigin::Minigin::m_Continue = true;
int minigin::Minigin::m_Width = 640;
int minigin::Minigin::m_Height = 480;

void minigin::Minigin::Initialize()
{
	try
	{
		m_Continue = true;

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw runtime_error(string("SDL_Init Error: ") + SDL_GetError());
		}

		m_pWindow = SDL_CreateWindow(
			"Programming 4 assignment",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_Width,
			m_Height,
			SDL_WINDOW_OPENGL
		);
		if (m_pWindow == nullptr)
		{
			throw runtime_error(string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		//initialize classes
		Renderer::GetInstance().Init(m_pWindow);
		Logger::Initialize();
		InputManager::GetInstance().Initialize(m_pWindow);

		//Engine input
		Logger::LogInfo(L"Press F2 to load the previous scene and F3 to load the next scene");
		Logger::LogInfo(L"Press ESC to quit the application");

		shared_ptr<Command> previousScene = make_shared<PreviousSceneCommand>(PreviousSceneCommand{});
		shared_ptr<Command> nextScene = make_shared<NextSceneCommand>(NextSceneCommand{});
		shared_ptr<Command> quitGame = make_shared<QuitCommand>(QuitCommand{});

		InputManager::GetInstance().AddInput(InputAction(previousScene, true, VK_F2, ControllerButton::none, InputTriggerState::Pressed));
		InputManager::GetInstance().AddInput(InputAction(nextScene, true, VK_F3, ControllerButton::none, InputTriggerState::Pressed));
		InputManager::GetInstance().AddInput(InputAction(quitGame, true, VK_ESCAPE, ControllerButton::none, InputTriggerState::Pressed));
	}
	catch (runtime_error error)
	{
		cout << "Runtime error:" << error.what() << endl;
	}
	catch (const exception & exc)
	{
		cout << exc.what();
	}
	catch (...)
	{
		cout << "Something unexpected went wrong in the engine initialization. Please report this issue to Robin De Paepe\n";
	}
}

void minigin::Minigin::Cleanup()
{
	Logger::Release();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void minigin::Minigin::Run()
{
	try
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();

		//game loop
		while (m_Continue)
		{
			//process input
			input.ProcessInput();

			//update
			time.Update();
			sceneManager.Update();

			//render
			renderer.Render();
		}
	}
	catch (const exception & exc)
	{
		cout << exc.what();
	}
	catch (...)
	{
		cout << "Something unexpected went wrong in the engine. Please report this issue to Robin De Paepe\n";
	}
	Cleanup();
}

void minigin::Minigin::QuitProgram()
{
	m_Continue = false;
}


