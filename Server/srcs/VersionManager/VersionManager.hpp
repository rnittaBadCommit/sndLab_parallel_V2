#ifndef VERSIONMANAGER_HPP
# define VERSIONMANAGER_HPP

# include <iostream>
namespace rnitta
{


class VersionManager
{
	public:
		// canonical
		VersionManager();
		VersionManager( const VersionManager& other );
		~VersionManager();
		VersionManager&	operator=( const VersionManager& other );

		// function
		bool	is_updateable();
		const std::string	fetch_README();
		void	update();
		void	reboot();
};


};	// namespace rnitta

#endif
