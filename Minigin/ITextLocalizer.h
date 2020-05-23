#pragma once
#include <memory>


	class ITextLocalizer
	{
		/**
		* https://gist.github.com/Zitrax/a2e0040d301bf4b8ef8101c0b1e3f1d5
		*/
		template<typename ... Args>
		static std::string stringFormatInternal(const std::string& format, Args&& ... args)
		{
			const size_t size = snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args) ...) + 1;
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1);
		}

	public:
		virtual ~ITextLocalizer() = default;

		/**
		 * Load the from the file with the given filename the given locale
		 */
		virtual void Load(const std::string& filename, const std::string& locale) = 0;
		virtual std::string Get(const std::string& key) = 0;

		template<typename ... Args>
		std::string GetFormat(const std::string& fmt, Args&& ... args) {
			return stringFormatInternal(Get(fmt), std::forward<Args>(args)...);
		}
	};
