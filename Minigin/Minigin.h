#pragma once
#include "MiniginPCH.h"

struct SDL_Window;

namespace minigin
{
	class Minigin final
	{
	public:
		//rule of 5
		Minigin() = default;
		~Minigin() = default;

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		//functions
		void Initialize();
		void Cleanup();
		void Run();
		static void QuitProgram();
	private:
		//datamembers
		SDL_Window* m_pWindow{};
		static bool m_Continue;
	};
}
