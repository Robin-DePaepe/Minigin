#include "MiniginPCH.h"
#include "LevelParser.h"
#include "BinaryReader.h"

const std::vector<LevelBlocks>& LevelParser::Parse(const std::string& file)
{
	m_Levels.clear();
	auto& reader{ minigin::BinaryReader::GetInstance() };

	reader.OpenFile("Resources/LevelsAndEnemies/" + file);

	for (int level = 0; level < m_LevelsToLoad; ++level)
	{
		std::vector<byte> bytes{};

		//a level contains 100 bytes of data
		for (size_t i{}; i < 100; ++i)
		{
			bytes.push_back(reader.Read<byte>());
		}
		AddLevel(bytes);
	}
	reader.Closefile();

	return m_Levels;
}

void LevelParser::AddLevel(std::vector<byte>& bytes)
{
	LevelBlocks level{};

	int y{ 0 };

	for (size_t i = 0; i < bytes.size();)
	{
		for (int j{}; j < 4; ++j)
		{
			const byte& byte = bytes[i];
			const int x{ j * 8 };

			level.Blocks[0 + x][y] = byte & 0b10000000;//this block is a tile
			level.Blocks[1 + x][y] = byte & 0b01000000;
			level.Blocks[2 + x][y] = byte & 0b00100000;
			level.Blocks[3 + x][y] = byte & 0b00010000;
			level.Blocks[4 + x][y] = byte & 0b00001000;
			level.Blocks[5 + x][y] = byte & 0b00000100;
			level.Blocks[6 + x][y] = byte & 0b00000010;
			level.Blocks[7 + x][y] = byte & 0b00000001;
			++i;
		}
		++y;
	}

	m_Levels.push_back(level);
}