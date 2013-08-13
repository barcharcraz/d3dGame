#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace utils {
	class not_found_error : public std::runtime_error {
	public:
		explicit not_found_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{

		}
	};
	class not_supported_error : public std::runtime_error {
	public:
		explicit not_supported_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{

		}
	};
}

#endif