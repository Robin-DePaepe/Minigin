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

using namespace std;
using namespace std::chrono;

void Minigin::Initialize()
{
	m_Continue = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
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
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	Logger::Initialize();
	InputManager::GetInstance().Initialize(m_Window);

	//Engine input
	Logger::LogInfo(L"Press F2 to load the previous scene and F3 to load the next scene");
	Logger::LogInfo(L"Press ESC to quit the application");

	shared_ptr<Command> previousScene = make_shared<PreviousSceneCommand>(PreviousSceneCommand{});
	shared_ptr<Command> nextScene = make_shared<NextSceneCommand>(NextSceneCommand{});
	shared_ptr<Command> quitGame = make_shared<QuitCommand>(QuitCommand{});

	InputManager::GetInstance().AddInput(InputAction(previousScene, VK_F2, ControllerButton::none, InputTriggerState::Pressed));
	InputManager::GetInstance().AddInput(InputAction(nextScene, VK_F3, ControllerButton::none, InputTriggerState::Pressed));
	InputManager::GetInstance().AddInput(InputAction(quitGame, VK_ESCAPE, ControllerButton::none, InputTriggerState::Pressed));
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<GameObject>();
	//go->SetTexture("background.jpg");
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->SetTexture("logo.png");
	//go->GetTransfrom()->SetPosition(216.f, 180.f);
	//scene.Add(go);


	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 32);
	//scene.Add(to);

	//scene.ShowFpsCounter(true);
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
	Cleanup();
}

void Minigin::QuitProgram()
{
	m_Continue = false;
}


