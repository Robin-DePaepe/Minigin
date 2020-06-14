#pragma once
#include "Command.h"
namespace minigin
{
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
}