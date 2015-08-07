#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__


#include <memory>
#include <map>
#include <typeindex>
#include <string>


#include <gal/stl/verbosity.hpp>
#include <gal/_release.hpp>
#include <gal/decl.hpp>
#include <gal/typedef.hpp>

#include <gal/registry.hpp>
#include <gal/managed_object.hpp>
#include <gal/process_index.hpp>
#include <gal/type_info.hpp>


#include <boost/thread.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/string.hpp>

#include <gal/stl/verbosity.hpp>
#include <gal/Flag.hpp>
//#include <gal/itf/release.hpp>
//#include <gal/itf/typedef.hpp>
//#include <gal/decl.hpp>
//#include <gal/itf/typedef.hpp>
//#include <gal/stl/verbosity.hpp>
#include <gal/shared.hpp>
//#include <gal/object_index.hpp>
//#include <gal/registry.hpp>

// gal/managed_object.hpp
// gal/registry.hpp

namespace gal {
/** @brief %shared.
	 *
	 * Avoid multiple enabled_shared_from_this bases.
	 * Provide common base for working with factory and map.
	 * Supply type info.
	 */
	class managed_object:
		virtual public gal::tmp::Verbosity<gal::managed_object>,
		virtual public gal::enable_shared_from_this<gal::managed_object>
	{
	public:
		using gal::tmp::Verbosity<gal::managed_object>::printv;
		using gal::enable_shared_from_this<gal::managed_object>::shared_from_this;

		DEFINE_FLAG(flag, ((INITIALIZED)(1<<0)))

		//typedef gal::registry<
		//	gal::object_index,
		//	gal::managed_object,
		//	gal::less_index> registry_type;
		//typedef gal::managed_process registry_type;
		typedef gal::registry_object registry_type;

		typedef std::map<gal::process_index, gal::object_index> map_type;

		friend class gal::registry<
			gal::object_index,
			gal::managed_object,
			gal::less_index>;
		friend class gal::registry_object;

		friend class boost::serialization::access;

		virtual void			init(registry_type * parent);
		//virtual void			init(gal::managed_object * parent);
		managed_object();
		virtual ~managed_object();
		
		
		/** get index for this process */
		gal::object_index		get_index();
		gal::object_index		get_index(gal::process_index) const;
		void				set_index(gal::object_index);


		virtual void			register_all(registry_type *);
		registry_type *			get_registry();
		registry_type const *		get_registry() const;
		bool				has_registry() const;

		void				print_index_table() const;
	protected:
		virtual void			change_process_index(
				gal::process_index p_old,
				gal::process_index p_new);

	private:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		registry_type *		_M_registry_parent;
	public:
		map_type		_M_index_table;




		



	private:
		void			load(
				boost::archive::polymorphic_iarchive & ar,
				unsigned int const & version);
		void			save(
				boost::archive::polymorphic_oarchive & ar,
				unsigned int const & version) const;
		BOOST_SERIALIZATION_SPLIT_MEMBER();
	public:
		flag				_M_flag;
		std::string			_M_name;
		/** @brief general mutex
		 *
		 * for thread-safe erasure from gal::stl::map
		 */
		boost::recursive_mutex		mutex_;
	};
}

#endif



