#include "Transceiver.hpp"

namespace rnitta
{
    

Transceiver::Transceiver()
: port_master_socket_vec_(1, 0)
{
	setup_();
}

Transceiver::~Transceiver()
{
	shutdown();
}

Transceiver::Transceiver( const std::vector<in_port_t> port_vec )
: port_master_socket_vec_(port_vec)
{
	setup_();
}

Transceiver::Transceiver( size_t num_port )
: port_master_socket_vec_(num_port, 0)
{
	setup_();
}

void	Transceiver::setup_()
{
	socklen_t	_socklen;
	struct sockaddr_in	_address;
	t_sockfd	_master_socket_fd;
	pollfd	_pollfd;

	_socklen = sizeof(_address);
	for (size_t i = 0; i < port_master_socket_vec_.size(); ++i)
	{
		if ((_master_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			throw std::runtime_error("Transceiver::Transceiver(): socket() fail");
		_pollfd.fd = _master_socket_fd;
		_pollfd.events = POLLIN | POLLERR_ALL;
		_pollfd.revents = 0;
		pollfd_vec_.push_back(_pollfd);

		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = INADDR_ANY;
		_address.sin_port = htons(port_master_socket_vec_[i]);
		if (bind(_master_socket_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
			throw std::runtime_error("Transceiver::Transceiver(): bind() fail");
		if (getsockname(_master_socket_fd, (struct sockaddr *)&_address, &_socklen) == -1)
			throw std::runtime_error("Transceiver::Transceiver(): getsockname() fail");
		port_master_socket_vec_[i] = ntohs(_address.sin_port);	// port_master_socket_vec_に0が設定されていた場合もOSに割り振られたポート番号で上書き
		if (listen(_master_socket_fd, 3) == -1)
			throw std::runtime_error("Transceiver::Transceiver(): listen() fail");
		sockfd_master_socket_vec_.push_back(_master_socket_fd);
		std::cout << "port[" << port_master_socket_vec_[i] << "] listening" << std::endl;
	}
	std::cout << "Transceiver successfully started" << std::endl;
}

void	Transceiver::shutdown()
{
	for (size_t i = 0; i < pollfd_vec_.size(); ++i)
	{
		close(pollfd_vec_[i].fd);
	}
}

void	Transceiver::register_message_to_send( const Message& __message )
{
	id_to_message_to_send_map_[__message.get_id()] += __message;
	pollfd_vec_[__message.get_id()].events = POLLIN | POLLOUT | POLLERR_ALL;
}

void	Transceiver::communicate()
{
	poll(&pollfd_vec_[0], pollfd_vec_.size(), -1);	// std::vectorのデータ領域は連続していることが保証されている。 
	for (size_t i = 0; i < pollfd_vec_.size(); ++i)
	{
		if (pollfd_vec_[i].revents & POLLERR)	// POLLRDHUPを検知した場合もreventsのPOLLINフラグが立ってしまうので、POLLRDHUPを先に見る必要あり
		{
			register_sockfd_to_close_(pollfd_vec_[i].fd);
		}
		else if (pollfd_vec_[i].revents & POLLHUP)
		{
			register_sockfd_to_close_(pollfd_vec_[i].fd);
		}
		else if (pollfd_vec_[i].revents & POLLRDHUP)
		{
			register_sockfd_to_close_(pollfd_vec_[i].fd);
		}
		else if (pollfd_vec_[i].revents & POLLIN)
		{
			pollfd_vec_[i].revents = 0;
			if (is_master_socket_fd_(pollfd_vec_[i].fd))
			{
				receive_from_new_client_(pollfd_vec_[i].fd);
			}
			else
			{
				receive_from_connected_client_(pollfd_vec_[i].fd);
			}
		}
		else if (pollfd_vec_[i].revents & POLLOUT)
		{
			pollfd_vec_[i].revents = 0;
			if (send_message_to_send_(pollfd_vec_[i].revents) == SEND_FINISHED)
				pollfd_vec_[i].events = POLLIN | POLLPRI;
		}
		else if (pollfd_vec_[i].revents & POLLPRI)
		{
			pollfd_vec_[i].revents = 0;
			receive_priority_message_(pollfd_vec_[i].fd);
		}
	}
	close_sockfd_to_close_();
}

const std::vector<Message>&	Transceiver::extract_message()
{
	return (received_message_vec_);
}

void	Transceiver::clear_message()
{
	received_message_vec_.clear();
}

void	Transceiver::receive_from_new_client_( const t_sockfd __sockfd_master_socket )
{
	t_sockfd	_sockfd_new_client;
	pollfd	_pollfd;
	
	if ((_sockfd_new_client = accept(__sockfd_master_socket, NULL, NULL)) == -1)
		throw std::runtime_error("Transceiver::receive_from_new_client_(): accept() fail");
	_pollfd.fd = _sockfd_new_client;
	_pollfd.events = POLLIN | POLLPRI | POLLERR_ALL;
	_pollfd.revents = 0;
	pollfd_vec_.push_back(_pollfd);
}

void	Transceiver::receive_from_connected_client_( const t_sockfd __sockfd_client_socket )
{
	char _buf[BUFFER_SIZE + 1];
	ssize_t	_ret_read;

	received_message_vec_.push_back(Message(__sockfd_client_socket, ""));
	std::vector<Message>::iterator	it_new_received_message = received_message_vec_.end() - 1;
	if ((_ret_read = read(__sockfd_client_socket, _buf, BUFFER_SIZE)) > 0)
	{
		_buf[_ret_read] = '\0';
		*it_new_received_message += std::string(_buf);
	}
	else if (_ret_read == -1)
		throw std::runtime_error("Transceiver::receive_from_connected_client_(): read() fail");
}

void	Transceiver::receive_priority_message_( const t_sockfd __sockfd_client_socket )
{
	char _buf[BUFFER_SIZE + 1];
	ssize_t	_ret_recv;

	received_message_vec_.push_back(Message(__sockfd_client_socket, "", true));
	std::vector<Message>::iterator	it_new_received_message = received_message_vec_.end() - 1;
	while ((_ret_recv = recv(__sockfd_client_socket, _buf, BUFFER_SIZE, MSG_OOB)) > 0)
	{
		_buf[_ret_recv] = '\0';
		*it_new_received_message += std::string(_buf);
	}
	if (_ret_recv == -1)
		throw std::runtime_error("Transceiver::receive_from_connected_client_(): read() fail");
}

bool	Transceiver::send_message_to_send_( const t_sockfd __sockfd_client_socket )
{
	Message&	_message_to_send = id_to_message_to_send_map_[__sockfd_client_socket];
	int			_ret_send;

	_ret_send = send(__sockfd_client_socket, _message_to_send.get_content().c_str(), _message_to_send.get_content().length(), 0);
	if (_ret_send == _message_to_send.get_content().length())	// 送信完了 
	{
		id_to_message_to_send_map_.erase(__sockfd_client_socket);
		return (SEND_FINISHED);
	}
	else
	{
		_message_to_send = _message_to_send.get_content().substr(_ret_send);
		return (!SEND_FINISHED);
	}
}

const bool	Transceiver::is_master_socket_fd_( const t_sockfd __sockfd ) const
{
	for (size_t i = 0; i < sockfd_master_socket_vec_.size(); ++i)
	{
		if (sockfd_master_socket_vec_[i] == __sockfd)
			return (true);
	}
	return (false);
}

void	Transceiver::register_sockfd_to_close_( const t_sockfd __sockfd )
{
	sockfd_to_close_stack_.push(__sockfd);
}

void	Transceiver::close_sockfd_to_close_()
{
	t_sockfd	_sockfd_to_close;
	std::vector<pollfd>::iterator	_it_pollfd_vec = pollfd_vec_.end();

	while (!sockfd_to_close_stack_.empty())
	{
		_sockfd_to_close = sockfd_to_close_stack_.top();
		sockfd_to_close_stack_.pop();
		while ((*--_it_pollfd_vec).fd != _sockfd_to_close)
			;
		_it_pollfd_vec = pollfd_vec_.erase(_it_pollfd_vec);
		close(_sockfd_to_close);
	}
}

};  // namespace rnitta
