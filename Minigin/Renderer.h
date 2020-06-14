#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Color;
struct SDL_Rect;

namespace minigin
{
	class Texture2D;

	class Renderer final : public Singleton<Renderer>
	{
	public:
		//rule of 5
		Renderer() = default;
		~Renderer() = default;

		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;

		//functions
		void Init(SDL_Window* pWindow);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderRect(SDL_Rect rect, SDL_Color color) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
	private:
		//datamembers
		SDL_Renderer* m_pRenderer{};
	};
}

