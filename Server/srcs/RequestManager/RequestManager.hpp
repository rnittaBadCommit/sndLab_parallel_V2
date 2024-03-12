#ifndef REQUESTMANAGER_HPP
# define REQUESTMANAGER_HPP

# include "../Request/Request.hpp"

namespace rnitta
{


class RequestManager
{
	public:
		// canonical
		RequestManager();
		RequestManager( const RequestManager& other );
		~RequestManager();
		RequestManager&	operator=( const RequestManager& other );

		// function
	private:
};


};	// namespace rnitta

#endif
