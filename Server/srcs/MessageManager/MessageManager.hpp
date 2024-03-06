#ifndef MESSAGEMANAGER_HPP
# define MESSAGEMANAGER_HPP

# include "../Message/Message.hpp"
# include "../Transceiver/Transceiver.hpp"
# include <map>
# include <vector>

namespace rnitta
{


class MessageManager
{
	public:
		typedef Message::t_id	t_id;
		// canonical
		MessageManager() = delete;
		MessageManager( const MessageManager& other );
		~MessageManager();
		MessageManager&	operator=( const MessageManager& other );

		MessageManager( Transceiver& transceiver );

		void	send_and_recv_message();
		const std::vector<Message>&	get_message_vec() const;
		void	register_message_to_send( const Message& message );
		void	clear_message_by_id( const t_id id );

	private:
		Transceiver&	transceiver_;
		std::map<t_id, Message>	id_to_message_map_;
		std::vector<Message>	message_updated_vec_;
	
};


};	// namespacce rnitta

#endif
