#ifndef TRANSCEIVER_HPP
# define TRANSCEIVER_HPP

# include <iostream>
# include "../Message/Message.hpp"

namespace rnitta
{


class Transceiver
{
	public:
		// canonical
		Transceiver();
		Transceiver( const Transceiver& other );
		~Transceiver();
		Transceiver&	operator=( const Transceiver& other );	


		// function
		void			send( const Message& message );
		const Message&	recv();

	private:
};


};	// namespace nritta


#endif
