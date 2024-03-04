#ifndef TRANSCEIVER_HPP
# define TRANSCEIVER_HPP

# include "../Message/Message.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <algorithm>

namespace rnitta
{


class Transceiver
{
	public:
		// typedef
		typedef int	t_sockfd;

		// canonical
		Transceiver();
		Transceiver( const Transceiver& other ) = delete;
		~Transceiver();
		Transceiver&	operator=( const Transceiver& other ) = delete;

		Transceiver( const std::vector<in_port_t> port_vec );
		Transceiver( size_t num_port );

		// function
		void		register_message_to_send( const Message& message );
		void		communicate();
		const std::vector<Message>&	extract_message();
		void		clear_message();
		void		shutdown();

	private:
		// typedef
		typedef short int		t_event;
		typedef size_t			t_i_pollfd_;
		static const t_event	POLLERR_ALL = POLLERR | POLLRDHUP | POLLHUP;
		static const bool		SEND_FINISHED = true;
		static const size_t		BUFFER_SIZE = 1000;
		std::vector<in_port_t>	port_master_socket_vec_;
		std::vector<pollfd>		pollfd_vec_;
		std::vector<t_sockfd>	sockfd_master_socket_vec_;
		std::stack<t_sockfd>	sockfd_to_close_stack_;

		std::vector<Message>	received_message_vec_;
		std::map<t_sockfd, Message>	sockfd_to_message_to_send_map_;
		
		void	setup_();
		const bool	is_master_socket_fd_( const t_sockfd sockfd ) const;
		void	receive_from_new_client_( const t_sockfd sockfd_master_socket );
		void	receive_from_connected_client_( const t_sockfd sockfd_client_socket );
		void	receive_priority_message_( const t_sockfd sockfd_client_socket );
		bool	send_message_to_send_( const t_sockfd sockfd_client_socket );
		void	register_sockfd_to_close_( const t_sockfd fd );
		void	close_sockfd_to_close_();
		const t_i_pollfd_	convert_sockfd_to_i_pollfd_( t_sockfd sockfd ) const;
};


};	// namespace nritta


#endif
