#pragma once

#include <string>

#ifndef LOG_DATE
# define LOG_DATE 1
#endif

#ifndef LOG_TIME
# define LOG_TIME 1
#endif

namespace cu::logger {

	enum Level {
		INFO,
		WARN,
		ERROR
	};

	void	log(Level lvl, const std::string &msg);

	inline void	info(const std::string &msg) { log(INFO, msg); }
	inline void	warn(const std::string &msg) { log(WARN, msg); }
	inline void	error(const std::string &msg) { log(ERROR, msg); }

}