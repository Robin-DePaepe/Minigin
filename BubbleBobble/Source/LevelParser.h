#pragma once

using byte = unsigned char;

struct LevelBlocks final
{
	const static int Width = 32;
	const static int Height = 25;
	bool Blocks[Width][Height];
};

class LevelParser final 
{
public:
//functions
	const std::vector<LevelBlocks>& Parse(const std::string& file);

private:
	//datamembers
	const int m_LevelsToLoad = 30;
	std::vector<LevelBlocks> m_Levels;

	//functions
	void AddLevel(std::vector<byte>& bytes);
};