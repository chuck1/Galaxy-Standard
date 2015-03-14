#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

/** @file shared.hpp
*/

#include <memory>
#include <map>
#include <typeindex>
#include <string>

#include <boost/thread.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/string.hpp>

#include <gal/itf/release.hpp>
#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>

#include <gal/type_info.hpp>

namespace gal { namespace itf {
	/** @brief %shared.
	 *
	 * Avoid multiple enabled_shared_from_this bases.
	 * Provide common base for working with factory and map.
	 * Supply type info.
	 */
	class shared:
		virtual public gal::type_info<gal::itf::shared>,
		virtual public gal::enable_shared_from_this<gal::itf::shared>,
		virtual public gal::itf::__release
	{
	public:
		using gal::enable_shared_from_this<gal::itf::shared>::shared_from_this;
		typedef gal::itf::registry R;
		friend class gal::itf::registry;
		friend class boost::serialization::access;

		R*				get_registry();
		/** @brief static get index
		 *
		 * for boost multi_index indexing
		 */
		static index_type const &	static_get_index(
				std::shared_ptr<gal::itf::shared> ptr);
	public:
		/// static member was resulting in mutliple ctor calls
		// which was reseting registry::next_ to 0
		// switch to using a non-static registry via foundation app
		//static gal::itf::registry				registry_;

		/// @TODO fix this
	public:
		shared();
		virtual ~shared();
		virtual void			init_shared(
				gal::itf::shared * const & parent);
		virtual void			release() = 0;
		/** */
	private:
		void			load(
				boost::archive::polymorphic_iarchive & ar,
				unsigned int const & version);
		void			save(
				boost::archive::polymorphic_oarchive & ar,
				unsigned int const & version) const;
		BOOST_SERIALIZATION_SPLIT_MEMBER();
	protected:
		/*
		 * index for finding this on this machine
		 */
		index_type			_M_index;
	public:
		index_type			get_index() const;
		/*
		 * index given to object by creation machine
		 * if not -1, implies that this machine was not the creation
		 * machine and therefore this object was loaded from an
		 * archive
		 */
		index_type			_M_index_creation;
	protected:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		gal::itf::shared *		_M_shared_parent;
	public:
		std::string			_M_name;
		/** @brief general mutex
		 *
		 * for thread-safe erasure from gal::stl::map
		 */
		boost::recursive_mutex		mutex_;
	};
}}

#endif



