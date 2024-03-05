#include "Utils.hpp"

using namespace rnitta;

int main()
{
	try
	{
		std::string	_output;
		std::cout << "ret: " << run_command("ls", _output) << ", output: " << _output << std::endl;
		std::cout << "ret: " << run_command("sh ./my_script.sh 2>&1", _output) << ", output: " << _output << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}
