#pragma once

struct _TTF_Font;

namespace minigin
{
	class Font final
	{
	public:
		//rule of 5 
		explicit Font(const string& fullPath, unsigned int size);
		~Font();

		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator= (const Font&) = delete;
		Font& operator= (const Font&&) = delete;

		//functions
		_TTF_Font* GetFont() const;
	private:
		//datamembers
		_TTF_Font* m_pFont;
		unsigned int m_Size;
	};
}
