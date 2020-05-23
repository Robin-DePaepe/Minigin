#include "MiniginPCH.h"
#include "TextLocalizer.h"
#include "Csv.h"

void TextLocalizer::Load(const std::string& filename, const std::string& locale) 
{
	m_TextMap.clear();

	io::CSVReader <2, io::trim_chars<' '>, io::no_quote_escape <';'>>in(filename);
	in.read_header(io::ignore_extra_column, "key", locale);

	string key, translation;
	while(in.read_row(key,translation)) m_TextMap.insert(std::pair<string,string>(key,translation));
}

std::string TextLocalizer::Get(const std::string& key) 
{
	if (m_TextMap.find(key) == m_TextMap.cend()) return "Error, text key not found";
	return m_TextMap.at(key);
}
