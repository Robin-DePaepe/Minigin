#pragma once
#include "Command.h"

class NextSceneCommand : public Command
{
	virtual void Execute()  override;
	virtual void Undo() override {};
};

class PreviousSceneCommand : public Command
{
	virtual void Execute()  override;
	virtual void Undo() override {};
};

class QuitCommand : public Command
{
	virtual void Execute()  override;
	virtual void Undo() override {};
};