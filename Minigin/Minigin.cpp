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

bool Minigin::m_Continue = true;

using namespace chrono;

void Minigin::Initialize()
{
	try
	{
	m_Continue = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw runtime_error(string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw runtime_error(string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	//initialize classes
	Renderer::GetInstance().Init(m_Window);
	Logger::Initialize();
	InputManager::GetInstance().Initialize(m_Window);

	//Engine input
	Logger::LogInfo(L"Press F2 to load the previous scene and F3 to load the next scene");
	Logger::LogInfo(L"Press ESC to quit the application");

	shared_ptr<Command> previousScene = make_shared<PreviousSceneCommand>(PreviousSceneCommand{});
	shared_ptr<Command> nextScene = make_shared<NextSceneCommand>(NextSceneCommand{});
	shared_ptr<Command> quitGame = make_shared<QuitCommand>(QuitCommand{});

	InputManager::GetInstance().AddInput(InputAction(previousScene, true, VK_F2, ControllerButton::none, InputTriggerState::Pressed));
	InputManager::GetInstance().AddInput(InputAction(nextScene, true, VK_F3, ControllerButton::none, InputTriggerState::Pressed));
	InputManager::GetInstance().AddInput(InputAction(quitGame,true, VK_ESCAPE, ControllerButton::none, InputTriggerState::Pressed));
	}
	catch(runtime_error error)
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

void Minigin::Cleanup()
{
	Logger::Release();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
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
	catch(const exception& exc)
	{
		cout << exc.what();
	}
	catch (...)
	{
		cout << "Something unexpected went wrong in the engine. Please report this issue to Robin De Paepe\n";
	}
	Cleanup();
}

void Minigin::QuitProgram()
{
	m_Continue = false;
}


