#include <vector>
#include <string>

namespace cu::string
{

std::vector<std::string> split(const std::string& str, char sep)
{
	std::vector<std::string> result;
	size_t start = 0;
	size_t i;

	for (i = 0; i < str.size(); ++i)
	{
		if (str[i] == sep)
		{
			if (i - start > 0)
			{
				std::string	res = str.substr(start, i - start);
				if (res.length())
					result.push_back(res);
			}
			start = i + 1;
		}
	}

	std::string	res = str.substr(start);
	if (res.length())
		result.push_back(res);
	return result;
}

}
