#ifndef NEB_FND_ARCHIVE_ARCHIVE_HPP
#define NEB_FND_ARCHIVE_ARCHIVE_HPP

#include <gal/decl.hpp>
#include <gal/mng/managed_object.hpp>

namespace gal { namespace archive {
	class archive:
		virtual public gal::mng::managed_object
	{
	public:
		typedef std::weak_ptr<gal::stl::factory_map> W_FM;

		archive();
//		gal::mng::managed_object *	get_shared_parent();
//		gal::mng::managed_object *	_M_shared_parent;
		W_FM		_M_factory_map;
	};
}}

#endif
