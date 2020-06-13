#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Texture;

/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D
{
public:
	SDL_Texture* GetSDLTexture() const;
	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();

	glm::vec2 GetSize() const;

	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D& operator= (const Texture2D&) = delete;
	Texture2D& operator= (const Texture2D&&) = delete;
private:
	SDL_Texture* m_Texture;
};

