#include "MiniginPCH.h"
#include "EngineInput.h"
#include "SceneManager.h"
#include "Minigin.h"

void minigin::NextSceneCommand::Execute()
{
	SceneManager::GetInstance().NextScene();
}

void minigin::PreviousSceneCommand::Execute()
{
	SceneManager::GetInstance().PreviousScene();
}

void minigin::QuitCommand::Execute()
{
	Minigin::QuitProgram();
}