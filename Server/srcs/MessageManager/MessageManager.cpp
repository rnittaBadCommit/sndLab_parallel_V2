#include "MessageManager.hpp"

namespace rnitta
{


MessageManager::MessageManager( const MessageManager& other )
{

}

MessageManager::~MessageManager()
{

}

MessageManager&	MessageManager::operator=( const MessageManager& other )
{
	if (this == &other)
		return (*this);

	return (*this);
}

MessageManager::MessageManager( Transceiver& __transceiver )
: transceiver_(__transceiver)
{

}

void	MessageManager::send_and_recv_message()
{
	message_updated_vec_.clear();
	transceiver_.communicate();
	const std::vector<Message>&	_message_vec = transceiver_.extract_message();
	for (auto _it_message_vec = _message_vec.begin(); _it_message_vec != _message_vec.end(); ++_it_message_vec)
	{
		if (id_to_message_map_.count((*_it_message_vec).get_id()))
		{
			id_to_message_map_[(*_it_message_vec).get_id()] += *_it_message_vec;
			std::cout << "message to add: " << (*_it_message_vec).get_content() << "id: " << (*_it_message_vec).get_id() << std::endl;
			std::cout << "new message" << id_to_message_map_[(*_it_message_vec).get_id()].get_content() << "id: " << (*_it_message_vec).get_id() << std::endl; 
		}
		else
			id_to_message_map_[(*_it_message_vec).get_id()] = *_it_message_vec;
		message_updated_vec_.push_back(id_to_message_map_[(*_it_message_vec).get_id()]);
	}
	const std::vector<Transceiver::t_sockfd>&	_sockfd_closed_vec = transceiver_.get_sockfd_closed_vec();
	for (auto _it_sockfd_closed_vec = _sockfd_closed_vec.begin(); _it_sockfd_closed_vec != _sockfd_closed_vec.end(); ++_it_sockfd_closed_vec)
	{
		if (id_to_message_map_.count(*_it_sockfd_closed_vec))
			id_to_message_map_.erase(*_it_sockfd_closed_vec);
	}
}

const std::vector<Message>&	MessageManager::get_message_vec() const
{ return (message_updated_vec_); }

void	MessageManager::register_message_to_send( const Message& __message )
{
	transceiver_.register_message_to_send(__message);
}

void	MessageManager::clear_message_by_id( const t_id __id )
{
	if (id_to_message_map_.count(__id))
		id_to_message_map_.erase(__id);
}

};	// namespace rnitta
