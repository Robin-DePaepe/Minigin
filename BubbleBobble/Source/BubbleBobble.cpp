#pragma once
#include "Minigin.h"
#include "SceneManager.h"
#include"GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextObject.h"

#include "MainMenu.h"
#include "Level.h"

int main()
{
	minigin::Minigin engine;

	//init the engine
	engine.Initialize();

	// tell the resource manager where he can find the game data
	minigin::ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");

	auto spMainMenu = make_shared<MainMenu>(L"Main Menu");
	auto spLevel = make_shared<Level>(L"Level");

	minigin::SceneManager& sceneManager = minigin::SceneManager::GetInstance();

	sceneManager.AddGameScene(spMainMenu);
	sceneManager.AddGameScene(spLevel);


	engine.Run();
}