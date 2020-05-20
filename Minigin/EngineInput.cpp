#include "MiniginPCH.h"
#include "EngineInput.h"
#include "SceneManager.h"
#include "Minigin.h"

void NextSceneCommand::Execute()
{
	SceneManager::GetInstance().NextScene();
}

void PreviousSceneCommand::Execute()
{
	SceneManager::GetInstance().PreviousScene();
}

void QuitCommand::Execute()
{
	Minigin::QuitProgram();
}