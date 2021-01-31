#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <string>
#include <vector>
namespace helix
{
	class IOManager
	{
	public:
		static bool ReadFileToBuffer(const std::string &path, std::vector<char> &buffer);
	};
}
#endif
