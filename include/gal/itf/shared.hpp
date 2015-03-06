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

#include <gal/itf/release.hpp>
#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>

namespace gal {
	namespace itf {
		/** @brief %shared.
		 *
		 * Avoid multiple enabled_shared_from_this bases.
		 * Provide common base for working with factory and map.
		 * Supply type info.
		 */
		class shared:
			public std::enable_shared_from_this<gal::itf::shared>,
			virtual public gal::itf::__release
		{
			public:
				typedef gal::itf::registry R;
				friend class gal::itf::registry;
				R*					get_registry();
				/** @brief static get index
				 *
				 * for boost multi_index indexing
				 */
				static index_type const &		static_get_index(std::shared_ptr<gal::itf::shared> ptr);
			public:
				/// static member was expleriencing in mutliple ctor calls which was reseting registry::next_ to 0
				// switch to using a non-static registry via foundation app
				//static gal::itf::registry				registry_;
			
				/// @TODO fix this
			public:
				shared();
				/** @brief destructor */
				virtual ~shared();
				/** @brief init */
				virtual void				init_shared(gal::itf::shared * const & parent);
				virtual void				release() = 0;
				/** @brief hash code */
				hash_type				hash_code() const;
				/** */
				std::string				name() const;
				/** */
				template<class A> void			serialize(A & ar, unsigned int const v)
				{
					ar & BOOST_SERIALIZATION_NVP(_M_index);
					ar & BOOST_SERIALIZATION_NVP(_M_name);
				}
				index_type				get_index() const;
			private:
				index_type				_M_index;
			protected:
				/**
				 * used to find the gal::itf::regisry and register this
				 */
				gal::itf::shared *			_M_shared_parent;
			public:
				std::string				_M_name;
				/** @brief general mutex
				 *
				 * for thread-safe erasure from gal::stl::map
				 */
				boost::recursive_mutex			mutex_;
		};
	}
}

#endif



