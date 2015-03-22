#ifndef NEB_FND_ARCHIVE_ARCHIVE_HPP
#define NEB_FND_ARCHIVE_ARCHIVE_HPP

//#include <gal/decl.hpp>
#include <gal/managed_object.hpp>

namespace gal { namespace archive {
	class archive:
		virtual public gal::managed_object
	{
	public:
		archive();
//		gal::managed_object *	get_shared_parent();
//		gal::managed_object *	_M_shared_parent;
	};
}}

#endif
