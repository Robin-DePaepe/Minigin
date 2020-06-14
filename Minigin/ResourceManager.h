#pragma once
#include "Singleton.h"

namespace minigin
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		//functions
		void Init(const string& data);
		shared_ptr<Texture2D> LoadTexture(const string& file) const;
		shared_ptr<Font> LoadFont(const string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		string m_DataPath;
	};
}
