#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>
#include <string_view>
namespace helix
{
	class Exception : public std::exception
	{
	public:
		Exception(std::string_view error);

		const char* what() const noexcept override { return m_error.c_str(); }
	private:
		std::string m_error{};
	};
}
#endif

