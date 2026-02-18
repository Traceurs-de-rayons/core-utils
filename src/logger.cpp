#include "logger.hpp"
#include "colors.hpp"

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
			case INFO:  return COLOR_GREEN  "[info]"  COLOR_RESET;
			case WARN:  return COLOR_YELLOW "[warn]"  COLOR_RESET;
			case ERROR: return COLOR_RED    "[error]" COLOR_RESET;
		}
		return "[unknown]";
	}

	void log(Level lvl, const std::string &msg)
	{
		std::ostream &out = (lvl == ERROR) ? std::cerr : std::cout;
		out << timestamp() << " " << levelToString(lvl) << " " << msg << std::endl;
	}

}