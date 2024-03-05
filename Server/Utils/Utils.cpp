#include "Utils.hpp"

namespace rnitta
{


int	run_command( const std::string __command, std::string& __output )
{
	const size_t	_BUFFER_SIZE = 1000;
	std::array<char, _BUFFER_SIZE>	_buf;
	FILE*	_pipe;

	_pipe = popen(__command.c_str(), "r");
	if (!_pipe)
		throw std::runtime_error("CommandRunner::run_command(): popen() fail");
	__output.clear();
	while (fgets(_buf.data(), _buf.size(), _pipe) != nullptr)
		__output += _buf.data();
	std::cout << __output << std::endl;
	int ret;
	ret = pclose(_pipe);
	if (ret == -1)
	{
		std::cerr << std::strerror(errno) << std::endl;
        throw std::runtime_error("CommandRunner::run_command(): pclose() fail");
	}
    return WEXITSTATUS(ret);
}


};	// namespace rnitta

