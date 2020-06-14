#pragma once
#include <fstream>

using namespace std;

//credits to mathieu for this logger (logger from overlord engine)

enum class LogLevel
{
	Info = 0x1,
	Warning = 0x2,
	Error = 0x4,
	FixMe = 0x8
};

class Logger
{
	//nested classes
private:
	class BaseLogger
	{
	protected:
		wostream* m_os = nullptr;
	public:
		BaseLogger() = default;
		virtual ~BaseLogger() = default;

		virtual void Log(const wstring& message)
		{
			(*m_os) << message;
			m_os->flush();
		}
	};

	class FileLogger : public BaseLogger
	{
		wstring m_filename;
	public:
		explicit FileLogger(const wstring& fileName)
			: m_filename(fileName)
		{
			m_os = new wofstream(m_filename.c_str());
		}
		~FileLogger()
		{
			if (m_os)
			{
				wofstream* of = static_cast<wofstream*>(m_os);
				of->close();
				delete m_os;
			}
		}
	};

	class ConsoleLogger : public BaseLogger
	{
	public:
		ConsoleLogger()
		{
			m_os = &wcout;
		}
	};

public:
	static void Initialize();
	static void Release();
	static int StartPerformanceTimer();
	static double StopPerformanceTimer(int timerId);

	static void Log(LogLevel level, const wstring& msg, bool includeTimeStamp = false);
	static void LogFormat(LogLevel level, const wchar_t* format, ...);
	static void LogInfo(const wstring& msg, bool includeTimeStamp = false);
	static void LogWarning(const wstring& msg, bool includeTimeStamp = false);
	static void LogError(const wstring& msg, bool includeTimeStamp = false);
	static void LogFixMe(const wstring& source, bool includeTimeStamp = false);
	static bool LogHResult(HRESULT hr, const wstring& origin, bool includeTimeStamp = false);
	static void StartFileLogging(const wstring& fileName);
	static void StopFileLogging();

#pragma warning(push)
#pragma warning(disable: 26812)
	static void BreakOnLog(LogLevel level, bool doBreak) {
		doBreak ? m_BreakBitField |= static_cast<char>(level)
			: m_BreakBitField &= ~static_cast<char>(level);
	}
#pragma warning(pop)

private:
	Logger(void) {};
	~Logger(void) {};


	static void ReleaseLoggers()
	{
		delete m_ConsoleLogger;
		delete m_FileLogger;
	};
	//TIMER 
	static double m_PcFreq;
	static const int MAX_PERFORMANCE_TIMERS = 10;
	static __int64 m_PerformanceTimerArr[MAX_PERFORMANCE_TIMERS];

	static HANDLE m_ConsoleHandle;

	static ConsoleLogger* m_ConsoleLogger;
	static FileLogger* m_FileLogger;
	static char m_BreakBitField;

	static wchar_t* m_ConvertBuffer;
	static const size_t m_ConvertBufferSize = 1024;

	friend class Game;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Logger(const Logger& obj) = delete;
	Logger& operator=(const Logger& obj) = delete;
};
