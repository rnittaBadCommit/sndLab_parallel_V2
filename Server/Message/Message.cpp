#include "Message.hpp"

namespace rnitta
{


Message::Message()
: id_(-1)
{

}

Message::Message( const Message& other )
: content_(other.content_), id_(other.id_)
{

}

Message::~Message()
{

}

Message&	Message::operator=( const Message& other )
{
	if (this == &other)
		return (*this);
	
	content_ = other.content_;
	id_ = other.id_;
	return (*this);
}

Message::Message( const std::string content, const t_id id )
: content_(content), id_(id)
{

}

void	Message::set_content( const std::string content )
{ content_ = content; }

void	Message::set_id( const t_id id )
{ id_ = id; }

const std::string	Message::get_content() const
{ return (content_); }

const Message::t_id	Message::get_id() const
{ return (id_); }

};	// namespace rnitta
