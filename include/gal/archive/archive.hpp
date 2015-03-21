#ifndef NEB_FND_ARCHIVE_ARCHIVE_HPP
#define NEB_FND_ARCHIVE_ARCHIVE_HPP

#include <gal/decl.hpp>

namespace gal { namespace archive {
	class archive
	{
	public:
		archive();
		gal::managed_object *	get_shared_parent();
		gal::managed_object *	_M_shared_parent;
	};
}}

#endif
