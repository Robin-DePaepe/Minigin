#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::vec2 Texture2D::GetSize() const
{
	glm::vec2 size{};

	if (m_Texture == nullptr) return size;

	int w, h;
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &w, &h);

	return size;
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;

	int w, h;
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &w, &h);

	std::cout << w << "          " << h << std::endl;
}
