#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

minigin::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

glm::vec2 minigin::Texture2D::GetSize() const
{
	glm::vec2 size{};

	if (m_pTexture == nullptr) return size;

	int w, h;
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &w, &h);

	size.x = float(w);
	size.y = float(h);

	return size;
}

SDL_Texture* minigin::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

minigin::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}
