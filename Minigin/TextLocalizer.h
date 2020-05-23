#pragma once
#include <string>
#include <map>
#include "ITextLocalizer.h"

using namespace std;

	class TextLocalizer final : public ITextLocalizer
	{
	public:
	void Load(const std::string& filename, const std::string& locale) override;
	std::string Get(const std::string& key) override;

	private:
		std::map<std::string, string> m_TextMap;
	};

