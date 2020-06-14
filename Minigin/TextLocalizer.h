#pragma once
#include <string>
#include <map>
#include "ITextLocalizer.h"

namespace minigin
{
	class TextLocalizer final : public ITextLocalizer
	{
	public:
		void Load(const string& filename, const string& locale) override;
		string Get(const string& key) override;

	private:
		map<string, string> m_TextMap;
	};
}
