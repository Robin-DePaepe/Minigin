#pragma once
#include "MiniginPCH.h"

struct SDL_Window;

class Minigin
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	MINIGIN_ENTRYPOINT void Run();
private:
	SDL_Window* m_Window{};
};
