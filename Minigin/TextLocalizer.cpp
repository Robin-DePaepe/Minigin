#include "MiniginPCH.h"
#include "TextLocalizer.h"
#include "Csv.h"

void minigin::TextLocalizer::Load(const string& filename, const string& locale)
{
	m_TextMap.clear();

	io::CSVReader <2, io::trim_chars<' '>, io::no_quote_escape <';'>>in(filename);
	in.read_header(io::ignore_extra_column, "key", locale);

	string key, translation;
	while(in.read_row(key,translation)) m_TextMap.insert(pair<string,string>(key,translation));
}

string minigin::TextLocalizer::Get(const string& key)
{
	if (m_TextMap.find(key) == m_TextMap.cend()) return "Error, text key not found";
	return m_TextMap.at(key);
}
