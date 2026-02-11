#include "logger.hpp"

#include <iomanip>
#include <iostream>

namespace cu::logger {

	static std::string timestamp()
	{
		std::time_t now = std::time(NULL);
		std::tm *tm = std::localtime(&now);

		char buffer[100];

	#if LOG_DATE && LOG_TIME
		strftime(buffer, 99, "%Y/%m/%d %H:%M:%S", tm);
	#elif LOG_DATE
		strftime(buffer, 99, "%Y/%m/%d", tm);
	#elif LOG_TIME
		strftime(buffer, 99, "%H:%M:%S", tm);
	#else
		buffer[0] = '\0';
	#endif

		return buffer;
	}

	static std::string levelToString(Level lvl)
	{
		switch (lvl)
		{
			case INFO:  return "\033[32m[info]\033[0m";
			case WARN:  return "\033[33m[warn]\033[0m";
			case ERROR: return "\033[31m[error]\033[0m";
		}
		return "[unknown]";
	}

	void log(Level lvl, const std::string &msg)
	{
		std::ostream &out = (lvl == ERROR) ? std::cerr : std::cout;
		out << timestamp() << " " << levelToString(lvl) << " " << msg << std::endl;
	}

}