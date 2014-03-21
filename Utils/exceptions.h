#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace utils {
	class unsupported_format_error : public std::runtime_error {
	public:
		explicit unsupported_format_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{

		}
	};
	class not_found_error : public std::runtime_error {
	public:
		explicit not_found_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{

		}
	};
	class file_not_found_error : public std::runtime_error {
	public:
		explicit file_not_found_error(const std::string& what_arg)
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
	class unsupported_conversion_error : public std::runtime_error {
	public:
		explicit unsupported_conversion_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{
			
		}
	};
	class precondition_error : public std::logic_error {
	public:
		explicit precondition_error(const std::string& what_arg)
			: logic_error(what_arg)
		{

		}
	};
	class graphics_api_error : public std::runtime_error {
	public:
		explicit graphics_api_error(const std::string& what_arg)
			: runtime_error(what_arg)
		{
			
		}
	};
    class invalid_enum_error : public std::logic_error {
    public:
        explicit invalid_enum_error(const std::string& what_arg)
            : logic_error(what_arg) {}
    };
	
}

#endif