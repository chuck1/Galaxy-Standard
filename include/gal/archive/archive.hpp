#ifndef NEB_FND_ARCHIVE_ARCHIVE_HPP
#define NEB_FND_ARCHIVE_ARCHIVE_HPP

#include <gal/std/decl.hpp>

namespace gal { namespace archive {
	class archive
	{
	public:
		archive();
		gal::itf::shared *	get_shared_parent();
		gal::itf::shared *	_M_shared_parent;
	};
}}

#endif
