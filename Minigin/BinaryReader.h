#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Singleton.h"

using namespace std;
using byte = unsigned char;

namespace minigin
{
	class BinaryReader : public Singleton<BinaryReader>
	{
	public:
		//rule of 5
		BinaryReader() = default;
		~BinaryReader() = default;

		BinaryReader(const BinaryReader& other) = delete;
		BinaryReader(BinaryReader&& other) = delete;
		BinaryReader& operator=(const BinaryReader& other) = delete;
		BinaryReader& operator=(BinaryReader&& other) = delete;

		//functions
		void OpenFile(const string& file);
		void Closefile();

		template <typename T>
		T Read();

	private:
		//datamembers
		ifstream m_Reader;
	};


	void BinaryReader::OpenFile(const string& file)
	{
		m_Reader.open(file, ios::in | ios::binary);
	}

	inline void BinaryReader::Closefile()
	{
		m_Reader.close();
	}

	template<typename T>
	T BinaryReader::Read()
	{
		char data[sizeof(T)];

		if (m_Reader.is_open() && m_Reader.good())
		{
			m_Reader.read(data, sizeof(T));
		}
		else	Logger::LogError(L"BinaryReader::Read > Error trying to read file.");

		return static_cast<T>(*data);
	}

	template<>
	wstring BinaryReader::Read()
	{
		wstringstream ss;

		if (m_Reader.is_open() && m_Reader.good())
		{
			int stringLength = int(Read<char>());

			for (int i = 0; i < stringLength; ++i) ss << Read<char>();
		}
		else	Logger::LogError(L"BinaryReader::Read > Error trying to read file.");

		return wstring(ss.str());
	}
}