#include "MessageManager.hpp"
using namespace rnitta;

int main()
{
	try
	{
		MessageManager	_messageManager;
		std::vector<Message>	_message_vec;
		while (1)
		{
			_messageManager.send_and_recv_message();
			const std::vector<Message>&	_message_vec = _messageManager.get_message_vec();
			for (auto _it_message_vec = _message_vec.begin(); _it_message_vec != _message_vec.end(); ++_it_message_vec)
			{
				std::cout << "ID: " << (*_it_message_vec).get_id() << ", Content: [" << (*_it_message_vec).get_content() << "]" << std::endl;
				_messageManager.register_message_to_send(*_it_message_vec);
			}
		}
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
}
