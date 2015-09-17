#ifndef NEBULA_UTIL_WRAPPERTYPED_HH
#define NEBULA_UTIL_WRAPPERTYPED_HH

#include <map>
#include <exception>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

//#include <Nebula/App/BaseFactory.hh>

#include <gal/stl/HashCode.hpp>
#include <gal/mng/managed_object.hpp>
#include <gal/stl/factory.hpp>
#include <gal/verb/Verbosity.hpp>
#include <gal/dll/helper.hpp>
#include <gal/stl/wrapper_util/error.hpp> // gal/stl/wrapper_util/error.hpp
#include <gal/archive/archive.hpp>

namespace ba = boost::archive;
namespace bs = boost::serialization;

namespace gal { namespace stl {


	class wrapper_base:
		virtual public gal::verb::Verbosity< gal::stl::wrapper_base >
	{
	public:
		using gal::verb::Verbosity< gal::stl::wrapper_base >::printv;
		using gal::verb::Verbosity< gal::stl::wrapper_base >::init_verb;
	};

	template< typename T_, typename S_ = std::shared_ptr<T_> >
	class wrapper:
		virtual public gal::stl::wrapper_base,
		virtual public gal::mng::managed_object
	{
	public:
		typedef T_				T;
		typedef S_				S;

		using gal::stl::wrapper_base::printv;
		using gal::stl::wrapper_base::init_verb;

		typedef std::shared_ptr< factory<T> >	S_F;
		typedef std::weak_ptr< factory<T> >	W_F;


		struct LoadType
		{
			enum
			{
				
			};
		};
		struct nullptrException: std::exception
		{
			virtual const char *	what()
			{
				return "null ptr";
			}
		};
		wrapper() 
			//factory(factory<T>::default_factory)
		{
			//assert(!factory.expired());
		}
		wrapper(S && ptr):
			ptr_(std::move(ptr))
			//factory(factory<T>::default_factory)
		{
			assert(ptr_);
		}
		wrapper(wrapper<T, S_> const & w):
			ptr_(w.ptr_),
			_M_factory(w._M_factory)
		{
			assert(ptr_);
		}
		wrapper(wrapper<T, S_>&& w):
			ptr_(std::move(w.ptr_)),
			_M_factory(std::move(w._M_factory))
		{
			assert(ptr_);
		}
		virtual ~wrapper()
		{
		}
		void				set_factory(S_F f)
		{
			assert(f);
			_M_factory = f;
		}
		S_F				get_factory()
		{
			auto f = _M_factory.lock();
			if(!f) {
				gal::error::backtrace bt; bt.calc();
				throw gal::stl::wrapper_util::null_factory(bt);
			}
			return f;
		}
		virtual void			v_check_delete()
		{
		}
		void				release()
		{
		}
		/** @brief %Load */
		template<class Archive>
		void			save(
				Archive & ar,
				unsigned int const & version) const
		{
			if(!ptr_) throw nullptrException();

			// determine if created statically or by dll
			auto del = std::get_deleter<gal::dll::deleter>(
					ptr_);

			printv(DEBUG, "del = %p\n", del);

			int load_type;
			if(del) {
				printv(DEBUG, "dynamic\n");

				load_type = 1;					
				ar << BOOST_SERIALIZATION_NVP(load_type);

				auto hi = del->getHelperInfo();

				ar << bs::make_nvp("helper", hi);
			} else {
				printv(DEBUG, "static\n");

				load_type = 0;
				ar << BOOST_SERIALIZATION_NVP(load_type);

				gal::hash_type h = ptr_->hash_code();
				std::string n = ptr_->name();

				printv(DEBUG, "name     = %s\n", n.c_str());
				printv(DEBUG, "hashcode = %lu\n", h);

				ar << bs::make_nvp("hashcode", h);
			}

			//ar << bs::make_nvp("object", *ptr_);
			ptr_->v_save(ar);
		}
		template<class Archive>
		void			load(
				Archive & ar,
				unsigned int const & version)
		{
			printv_func(DEBUG);

			int load_type;
			ar >> BOOST_SERIALIZATION_NVP(load_type);

			if(load_type == 0) {
				load_0(ar, version);
			} else if(load_type == 1) {
				load_1(ar, version);
			} else {
				printf("invalid load type %i\n", load_type);
				assert(0);
			}
		
			if(gal::mng::managed_object::has_registry()) {
				auto r = get_registry();
				//ptr_->init_shared(_M_registry_parent);
				ptr_->gal::mng::managed_object::init(r);
			} else {
				auto ar1 = dynamic_cast<gal::archive::archive*>(&ar);
				assert(ar1);
				//ptr_->init_shared(ar1->get_shared_parent());
				//ptr_->gal::mng::managed_object::init(ar1->get_shared_parent());
				ptr_->gal::mng::managed_object::init(ar1->get_registry());
			}
			
			// read object data
			//ar >> bs::make_nvp("object", *ptr_);
			//ar >> bs::make_nvp("object", ptr_);
			ptr_->v_load(ar);
		}
		/*
		 * load static object
		 */
		template<class Archive>
		void			load_0(
				Archive & ar,
				unsigned int const & version)
		{
			printv(DEBUG, "static object\n");

			gal::hash_type h;

			ar >> bs::make_nvp("hashcode", h);

			printv(DEBUG, "hashcode = %lu\n", h);

			auto fs = get_factory();
			
			// allocate the object
			ptr_ = fs->template alloc<>(h);
		}
		/*
		 * load dynamic object
		 */
		template<class Archive>
		void			load_1(
				Archive & ar,
				unsigned int const & version)
		{
			printv(DEBUG, "dynamic object\n");
			
			gal::dll::helper_info hi;
			ar >> bs::make_nvp("helper", hi);

			// must add to helper_info: search path(s)
			// for .so files
			// search path(s) will be passed to this
			// by calling code

			auto fs = get_factory();

			// allocate the object
			ptr_ = fs->template alloc<gal::dll::helper_info&>(
					hi.base_hc, hi);
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER();
		/*
		static gal::object_index const &			static_get_index(gal::stl::wrapper<T, S_> const & wrap)
		{
			if(wrap.ptr_->_M_index == -1) {
				printv(CRITICAL, "warning: gal::mng::managed_object object is uninitialized\n");
				throw 0;
			}
			return wrap.ptr_->i_;
		}
		*/
	public:
		S				ptr_;
		W_F				_M_factory;
	};
}}

//template< typename T, typename S > int gal::verb::Verbosity< gal::stl::wrapper<T, S> >::_M_level = DEBUG;

#endif



