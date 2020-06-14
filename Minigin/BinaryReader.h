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
		if (m_Reader.is_open() && m_Reader.good())
		{
			char* pData{};
			m_Reader.read(pData, sizeof(T));

			return static_cast<T>(*size);
		}
		else	throw exception("BinaryReader::Read > Error trying to read file.");
	}

	template<>
	wstring BinaryReader::Read()
	{
		if (m_Reader.is_open() && m_Reader.good())
		{
			int stringLength = int(Read<char>());

			wstringstream ss;

			for (int i = 0; i < stringLength; ++i) ss << Read<char>();

			return wstring(ss.str());
		}
		else	throw exception("BinaryReader::Read > Error trying to read file.");
	}
}