#ifndef SERVER_HPP
# define SERVER_HPP

# include "Transceiver/Transceiver.hpp"
# include "MessageManager/MessageManager.hpp"
namespace rnitta
{


class Server
{
	public:
		// canonical
		Server();
		Server( const Server& other ) = delete;
		~Server();
		Server&	operator=( const Server& other ) = delete;
	
	private:
		Transceiver	transceiver_;
		MessageManager	messageManager_;
	
};


};	// namespace rnitta

#endif
