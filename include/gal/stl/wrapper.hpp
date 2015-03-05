#ifndef NEBULA_UTIL_WRAPPERTYPED_HH
#define NEBULA_UTIL_WRAPPERTYPED_HH

#include <map>
#include <exception>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

//#include <Nebula/App/BaseFactory.hh>

#include <gal/stl/HashCode.hpp>
#include <gal/itf/shared.hpp>
#include <gal/stl/factory.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/dll/helper.hpp>

namespace ba = boost::archive;

namespace gal { namespace stl {
	template<typename T>
	class wrapper:
		public gal::tmp::Verbosity< wrapper<T> >,
		virtual public gal::itf::shared
	{
		public:
			using gal::tmp::Verbosity< wrapper<T> >::printv;
			typedef std::weak_ptr< factory<T> >			factory_weak;
			typedef std::shared_ptr<T>				shared;
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
			/** @brief constructor
			*/
			wrapper(): 
				factory_(factory<T>::default_factory_)
		{
			printv(DEBUG, "wrapper default ctor\n");
			assert(!factory_.expired());
		}
			/** @brief constructor
			*/
			wrapper(shared ptr):
				ptr_(ptr),
				factory_(factory<T>::default_factory_)
		{
			printv(DEBUG, "wrapper ctor 1\n");
			assert(ptr_);
		}
			wrapper(wrapper<T> const & w):
				ptr_(w.ptr_),
				factory_(w.factory_)
		{
			printv(DEBUG, "wrapper copy ctor\n");
			assert(ptr_);
		}
			wrapper(wrapper<T>&& w):
				ptr_(std::move(w.ptr_)),
				factory_(std::move(w.factory_))
		{
			printv(DEBUG, "wrapper move ctor\n");
			assert(ptr_);
		}
		public:
			/** @brief Destructor */
			virtual ~wrapper()
			{
				printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
			}
			void					release()
			{
			}
			/** @brief %Load */
			template<class Archive> void		save(Archive & ar, unsigned int const & version) const
			{
				if(!ptr_) throw nullptrException();

				// determine if created statically or by dll
				auto del = std::get_deleter<gal::dll::deleter>(ptr_);

				printv(DEBUG, "del = %p\n", del);

				int load_type;
				if(del)
				{
					printv(DEBUG, "dynamic\n");

					load_type = 1;					
					ar << BOOST_SERIALIZATION_NVP(load_type);

					auto hi = del->getHelperInfo();

					ar << boost::serialization::make_nvp("helper", hi);
				}
				else
				{
					printv(DEBUG, "static\n");

					load_type = 0;
					ar << BOOST_SERIALIZATION_NVP(load_type);

					HashCode hc(ptr_->hash_code());
					ar << boost::serialization::make_nvp("hashcode", hc);
				}


				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			template<class Archive> void		load(Archive & ar, unsigned int const & version)
			{
				int load_type;
				ar >> BOOST_SERIALIZATION_NVP(load_type);

				if(load_type == 1) // dll
				{
					gal::dll::helper_info hi;
					ar >> boost::serialization::make_nvp("helper", hi);

					// must add to helper_info: search path(s) for .so files
					// search path(s) will be passed to this by calling code

					// get the factory
					auto fs = factory_.lock();
					assert(fs);

					// allocate the object
					ptr_ = fs->template alloc<gal::dll::helper_info&>(hi.base_hc, hi);
				}
				else
				{

					HashCode hc;
					ar >> boost::serialization::make_nvp("hashcode", hc);

					// get the factory
					auto fs = factory_.lock();
					assert(fs);

					// allocate the object
					ptr_ = fs->template alloc<>(hc.hc);
				}
				ptr_->init_shared(_M_shared_parent);
				// read objcet data
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}

			/** */
			BOOST_SERIALIZATION_SPLIT_MEMBER();
			static gal::itf::index_type const &			static_get_index(gal::stl::wrapper<T> const & wrap) {
				if(wrap.ptr_->_M_index == -1) {
					printv(CRITICAL, "warning: gal::itf::shared object is uninitialized\n");
					throw 0;
				}
				return wrap.ptr_->i_;
			}

		public:
			/** @brief Pointer */
			shared				ptr_;
			factory_weak			factory_;
	};


}
}

#endif



