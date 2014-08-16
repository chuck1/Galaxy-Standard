#ifndef NEBULA_UTIL_WRAPPERTYPED_HH
#define NEBULA_UTIL_WRAPPERTYPED_HH

#include <map>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

//#include <Nebula/App/BaseFactory.hh>

#include <gal/std/shared.hpp>
#include <gal/std/factory.hpp>

namespace gal {
	namespace stl {
		/** @brief wrapper
		 * class T must be derived from and registered with gal::std::Typed or exceptions will be thrown
		 */
		template<typename T> class wrapper {
			public:
				typedef sp::weak_ptr< factory<T> >			factory_weak;
				typedef sp::shared_ptr<T>				shared;
				/** */
				wrapper():
					factory_(factory<T>::default_factory_) //Neb::App::BaseFactory::global()->getFactoryDefault<T>()
			{
			}
				/** */
				wrapper(shared ptr):
					ptr_(ptr),
					factory_(factory<T>::default_factory_) //Neb::App::BaseFactory::global()->getFactoryDefault<T>())
			{
				assert(ptr_);
			}
				wrapper(wrapper<T> const & w):
					ptr_(w.ptr_),
					factory_(w.factory_)
			{
				assert(ptr_);
			}
				wrapper(wrapper<T>&& w):
					ptr_(::std::move(w.ptr_)),
					factory_(::std::move(w.factory_))
			{
				assert(ptr_);
			}
			public:
				/** @brief Destructor */
				virtual ~wrapper() {}
				/** @brief %Load */
				template<class Archive> void		load(Archive & ar, unsigned int const & version) {
					// get the code
					long int hash_code;
					ar >> boost::serialization::make_nvp("hash_code", hash_code);

					// get the factory
					auto fs = factory_.lock();
					assert(fs);

					// allocate the object

					ptr_ = fs->template alloc<>(hash_code);

					// read objcet data
					ar >> boost::serialization::make_nvp("object", *ptr_);
				}
				/** @brief %Save */
				template<class Archive> void		save(Archive & ar, unsigned int const & version) const {
					gal::std::hash_type hash_code = ptr_->hash_code();
					ar << boost::serialization::make_nvp("hash_code", hash_code);
					ar << boost::serialization::make_nvp("object", *ptr_);
				}
				/** */
				void					load(
						boost::archive::xml_iarchive & ar,
						unsigned int const & version) {
					// get the code
					::std::string name;
					ar >> boost::serialization::make_nvp("name", name);
					gal::std::hash_type hash = gal::std::shared::to_hash_code(name);

					// get the factory
					auto fs = factory_.lock();
					assert(fs);

					// allocate the object
					ptr_ = fs->template alloc<>(hash);

					// read objcet data
					ar >> boost::serialization::make_nvp("object", *ptr_);
				}
				/** */
				void					save(
						boost::archive::xml_oarchive & ar,
						unsigned int const & version) const {
					::std::string name = gal::std::shared::to_string(ptr_->hash_code());
					ar << boost::serialization::make_nvp("name", name);
					ar << boost::serialization::make_nvp("object", *ptr_);
				}
				BOOST_SERIALIZATION_SPLIT_MEMBER();
				static index_type const &			static_get_index(gal::std::wrapper<T> const & wrap) {
					if(wrap.ptr_->i_ == -1) {
						::std::cout << "warning: gal::std::shared object is uninitialized" << ::std::endl;
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



