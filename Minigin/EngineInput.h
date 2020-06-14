#pragma once
#include "Command.h"
namespace minigin
{
	class NextSceneCommand final : public Command
	{
		virtual void Execute()  override;
		virtual void Undo() override {};
	};

	class PreviousSceneCommand final : public Command
	{
		virtual void Execute()  override;
		virtual void Undo() override {};
	};

	class QuitCommand final : public Command
	{
		virtual void Execute()  override;
		virtual void Undo() override {};
	};
}