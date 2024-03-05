#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/wait.h>
# include <cerrno>
# include <cstring>

# include <fstream>

namespace rnitta
{

int	run_command( const std::string command, std::string& output );

};	// namespace rnitta

#endif
