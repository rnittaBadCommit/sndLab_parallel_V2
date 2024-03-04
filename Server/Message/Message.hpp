#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

namespace rnitta
{


class Message
{
	public:
		// typedef
		typedef	int			t_sockfd;
		typedef t_sockfd	t_id;

		// canonical & other constructor
		Message();
		Message( const Message& other );
		~Message();
		Message&	operator=( const Message& other );
		Message&	operator=( const std::string& other );
		Message&	operator+=( const std::string& content );
		Message&	operator+=( const Message& other );

		Message( const t_id id, const std::string content );
		Message( const t_id id , const std::string content, const bool is_priority );

		// getter & setter
		void				set_content( const std::string content );
		void				set_id( const t_id id );
		void				set_sockfd( const t_sockfd sockfd );
		void				set_is_priority( const bool is_priority );
		const std::string	get_content() const;
		const t_id			get_id() const;
		const t_sockfd		get_sockfd() const;
		const bool			get_is_priority() const;
	
	private:
		t_id			id_;
		std::string		content_;
		bool			is_priority_;
};


};	// namespace rnitta

#endif