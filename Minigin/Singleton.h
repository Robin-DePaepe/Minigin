#pragma once

namespace minigin
{
	template <typename T>
	class Singleton
	{
	public:
		//getter function
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		//rule of 5
		virtual ~Singleton() = default;

		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
	};
}