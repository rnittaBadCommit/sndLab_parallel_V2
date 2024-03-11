#include "Request.hpp"

namespace rnitta
{


Request::Request()
{

}

Request::Request( const Request& other )
: id_(other.id_), type_(other.type_), content_(other.content_)
{

}

Request::~Request()
{

}

Request&	Request::operator=( const Request& other)
{
	if (this == &other)
		return (*this);


	return (*this);	
}

Request::Request( const Message& __message )
: id_(__message.get_id())
{
	std::string _message_content = __message.get_content();
	std::string _tmp_type;

	size_t	_space_pos = _message_content.find(' ');
	if (_space_pos == std::string::npos)
	{
		_tmp_type = _message_content;
		content_ = "";
	}
	else
	{
		_tmp_type = _message_content.substr(0, _space_pos);
		content_ = _message_content.substr(_space_pos + 1);
	}
	set_type_(_tmp_type);
}

const Request::t_id	Request::get_id() const
{ return (id_); }

const Request::Type	Request::get_type() const
{ return (type_); }

const std::string&	Request::get_command() const
{ return (content_); }

const std::string&	Request::get_params() const
{ return (content_); }

void	Request::set_type_( const std::string& __type )
{
	if (__type == "COMMAND")
		type_ = COMMAND;
	else if (__type == "CHDIR")
		type_ = CHDIR;
	else if (__type == "UPDATE")
		type_ = UPDATE;
	else
		type_ = ERROR;
}


};	// namespace rnitta
