#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "../Message/Message.hpp"
# include <iostream>
namespace rnitta
{


class Request
{
	public:
		// typedef
		typedef Message::t_id	t_id;
		enum Type
		{
			COMMAND,
			CHDIR,
			UPDATE,
			ERROR,
		};

		// canonical
		Request();
		Request( const Request& other );
		~Request();
		Request&	operator=( const Request& other );
		Request( const Message& message );

		// getter
		const t_id	get_id() const;
		const Type	get_type() const;
		const std::string&	get_command() const;
		const std::string&	get_params() const;
	
	private:
		
		t_id	id_;
		Type	type_;
		std::string	content_;
		void	set_type_( const std::string& type );
		
};


};	// namespace rnitta

#endif
