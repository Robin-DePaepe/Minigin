#pragma once
#include "MiniginPCH.h"

struct SDL_Window;

class Minigin
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	 void Run();
	 void QuitProgram();
private:
	SDL_Window* m_Window{};
	bool m_Continue;
};
