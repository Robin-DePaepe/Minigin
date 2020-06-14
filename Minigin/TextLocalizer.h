#pragma once
#include <string>
#include <map>
#include "ITextLocalizer.h"

namespace minigin
{
	class TextLocalizer final : public ITextLocalizer
	{
	public:
		//rule of 5
		TextLocalizer() = default;
		~TextLocalizer() = default;

		TextLocalizer(const TextLocalizer& other) = delete;
		TextLocalizer(TextLocalizer&& other) = delete;
		TextLocalizer& operator=(const TextLocalizer& other) = delete;
		TextLocalizer& operator=(TextLocalizer&& other) = delete;

		//functions
		void Load(const string& filename, const string& locale) override;
		string Get(const string& key) override;

	private:
		//datamembers
		map<string, string> m_TextMap;
	};
}
