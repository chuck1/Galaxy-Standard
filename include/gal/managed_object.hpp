#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__


#include <memory>
#include <map>
#include <typeindex>
#include <string>


#include <gal/stl/verbosity.hpp>
#include <gal/itf/release.hpp>
#include <gal/decl.hpp>
#include <gal/itf/typedef.hpp>

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
		public gal::tmp::Verbosity<gal::managed_object>,
		virtual public gal::enable_shared_from_this<gal::managed_object>
	{
	public:
		using gal::tmp::Verbosity<gal::managed_object>::printv;
		using gal::enable_shared_from_this<gal::managed_object>::shared_from_this;
		
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

		friend class boost::serialization::access;

		virtual void			init(registry_type * parent);
		managed_object();
		virtual ~managed_object();
		/*
		 * get index for this process
		 */
		gal::object_index		get_index() const;
		gal::object_index		get_index(gal::process_index) const;
		//index_type			get_index_creation() const;
		void				set_index(gal::object_index);
		//void				set_index_creation(gal::object_index);
		virtual void			register_all(registry_type *);
		registry_type *			get_registry();
		registry_type const *		get_registry() const;
		void				change_process_index(
				long int old_pi,
				long int new_pi);
	public:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		registry_type *		_M_registry_parent;

		map_type		_M_index_table;


		/** @brief static get index
		 *
		 * for boost multi_index indexing
		 */
		//static index_type const &	static_get_index(
		//		std::shared_ptr<gal::managed_object> ptr);
	public:
		/// static member was resulting in mutliple ctor calls
		// which was reseting registry::next_ to 0
		// switch to using a non-static registry via foundation app
		//static gal::registry				registry_;

		/// @TODO fix this







	public:

		/** @brief static get index
		 *
		 * for boost multi_index indexing
		 */
		//static index_type const &	static_get_index(
		//		std::shared_ptr<gal::managed_object> ptr);
	public:
		/// static member was resulting in mutliple ctor calls
		// which was reseting registry::next_ to 0
		// switch to using a non-static registry via foundation app
		//static gal::registry				registry_;

		/// @TODO fix this
	public:
		//shared();
		//virtual ~shared();
		/** */
	private:
		void			load(
				boost::archive::polymorphic_iarchive & ar,
				unsigned int const & version);
		void			save(
				boost::archive::polymorphic_oarchive & ar,
				unsigned int const & version) const;
		BOOST_SERIALIZATION_SPLIT_MEMBER();
	public:
		std::string			_M_name;
		/** @brief general mutex
		 *
		 * for thread-safe erasure from gal::stl::map
		 */
		boost::recursive_mutex		mutex_;
	};
}

#endif



