#pragma once
#include <memory>

namespace minigin
{
	class ITextLocalizer
	{
		/**
		* https://gist.github.com/Zitrax/a2e0040d301bf4b8ef8101c0b1e3f1d5
		*/
		template<typename ... Args>
		static string stringFormatInternal(const string& format, Args&& ... args)
		{
			const size_t size = snprintf(nullptr, 0, format.c_str(), forward<Args>(args) ...) + 1;
			unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			return string(buf.get(), buf.get() + size - 1);
		}

	public:
		virtual ~ITextLocalizer() = default;

		/**
		 * Load the from the file with the given filename the given locale
		 */
		virtual void Load(const string& filename, const string& locale) = 0;
		virtual string Get(const string& key) = 0;

		template<typename ... Args>
		string GetFormat(const string& fmt, Args&& ... args) {
			return stringFormatInternal(Get(fmt), forward<Args>(args)...);
		}
	};
}