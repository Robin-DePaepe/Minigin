#pragma once
#include "Minigin.h"
#include "SceneManager.h"
#include"GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "TestScene1.h"
#include "TestScene2.h"

int main()
{
	Minigin engine;

	//init the engine
	engine.Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//testing
	auto spScene1 = make_shared<TestScene1>(L"Test zonder fps");
	auto spScene2 = make_shared<TestScene2>(L"Test met fps");
	

	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.AddGameScene(spScene1);
	sceneManager.AddGameScene(spScene2);

//	sceneManager.NextScene();

	engine.Run();
}