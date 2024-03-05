#include "Message.hpp"

namespace rnitta
{


Message::Message()
: id_(-1)
{

}

Message::Message( const Message& other )
: id_(other.id_), content_(other.content_), is_priority_(other.is_priority_)
{

}

Message::~Message()
{

}

Message&	Message::operator=( const Message& other )
{
	if (this == &other)
		return (*this);
	
	id_ = other.id_;
	content_ = other.content_;
	is_priority_ = other.is_priority_;
	return (*this);
}

Message&	Message::operator=( const std::string& other )
{
	content_ = other;
	return (*this);
}

Message&	Message::operator+=( const std::string& _content )
{
	content_ += _content;
	return (*this);
}

Message&	Message::operator+=( const Message& _other )
{
	if (id_ != _other.id_ || is_priority_ != _other.is_priority_)
		return (*this);
	content_ += _other.content_;
	return (*this);	
}

Message::Message( const t_id id, const std::string content )
: id_(id), content_(content), is_priority_(false)
{

}

Message::Message( const t_id id, const std::string content, bool is_priority )
: id_(id), content_(content), is_priority_(is_priority)
{

}

void	Message::set_content( const std::string content )
{ content_ = content; }

void	Message::set_id( const t_id id )
{ id_ = id; }

void	Message::set_sockfd( const t_sockfd __sockfd )
{ id_ = __sockfd; }

void	Message::set_is_priority( const bool is_priority )
{ is_priority_ = is_priority; }

const std::string	Message::get_content() const
{ return (content_); }

const Message::t_id	Message::get_id() const
{ return (id_); }

const Message::t_sockfd	Message::get_sockfd() const
{ return (id_); }

const bool	Message::get_is_priority() const
{ return (is_priority_); }

};	// namespace rnitta
