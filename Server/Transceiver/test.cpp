#include "Transceiver.hpp"
using namespace rnitta;

int main()
{
	try
	{
		std::vector<in_port_t>	_port_vec = {8080, 8081, 8082};
		Transceiver	transceiver(_port_vec);
		std::vector<Message>	_message_vec;
		while (1)
		{
			transceiver.communicate();
			_message_vec = transceiver.extract_message();
			std::cout << "test main 10" << std::endl;
			for (auto _it_message_vec = _message_vec.begin(); _it_message_vec != _message_vec.end(); ++_it_message_vec)
			{
				std::cout << "ID: " << (*_it_message_vec).get_id() << ", Content: [" << (*_it_message_vec).get_content() << "]" << std::endl;
				transceiver.register_message_to_send(*_it_message_vec);
			}
			std::cout << "test main " << std::endl;
		}
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
}
