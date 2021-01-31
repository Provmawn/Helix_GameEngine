#include "Exception.h"
namespace helix
{
	Exception::Exception(std::string_view error)
		: m_error{ error }
	{
	}
}
