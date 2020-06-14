#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* minigin::Font::GetFont() const {
	return m_pFont;
}

minigin::Font::Font(const string& fullPath, unsigned int size) : m_pFont(nullptr), m_Size(size)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr)
	{
		throw runtime_error(string("Failed to load font: ") + SDL_GetError());
	}
}

minigin::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}
