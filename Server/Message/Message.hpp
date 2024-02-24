#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

namespace rnitta
{


class Message
{
	public:
		// typedef
		typedef	int	t_id;

		// canonical & other constructor
		Message();
		Message( const Message& other );
		~Message();
		Message&	operator=( const Message& other );

		Message( const std::string content, const t_id id );

		// getter & setter
		void				set_content( const std::string content );
		void				set_id( const t_id id );
		const std::string	get_content() const;
		const t_id			get_id() const;
	
	private:
		std::string		content_;
		t_id				id_;
};


};	// namespace rnitta

#endif