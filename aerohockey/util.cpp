#include "util.hpp"

#define RUNNING_WINDOWS

#ifdef RUNNING_WINDOWS
	#include <direct.h> // _getcwd
	std::string getcwd_string() {
		char* buffer;

		if ((buffer = _getcwd(NULL, 0)) == NULL)
		{
			std::cout << "Failed to retrieve CWD, problems with texture loading may occur." << std::endl;
			return "";
		}
		else
		{
			std::cout << "Current working directory: " << std::string(buffer);
			return std::string(buffer);
			free(buffer);
		}
	}
#elif defined RUNNING_LINUX
	#include <unistd.h> // getcwd
	std::string getcwd_string() {
		int PATH_MAX = 255;
		char buff[PATH_MAX];
		getcwd(buff, PATH_MAX);
		std::string cwd(buff);
		return cwd;
	}
#endif


float len2 (sf::Vector2f const v)
{
    return v.x * v.x + v.y * v.y;
}


float dot (sf::Vector2f const v1, sf::Vector2f const v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}


float dist2 (sf::Vector2f const & p1, sf::Vector2f const & p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
