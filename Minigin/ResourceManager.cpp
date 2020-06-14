#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void minigin::ResourceManager::Init(const string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw runtime_error(string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw runtime_error(string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw runtime_error(string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

shared_ptr<minigin::Texture2D>minigin::ResourceManager::LoadTexture(const string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw runtime_error(string("Failed to load texture: ") + SDL_GetError());
	}
	return make_shared<Texture2D>(texture);
}

shared_ptr<minigin::Font> minigin::ResourceManager::LoadFont(const string& file, unsigned int size) const
{
	return make_shared<Font>(m_DataPath + file, size);
}
