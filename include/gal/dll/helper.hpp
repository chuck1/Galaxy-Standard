#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {

	template<typename H> struct deleter;

	struct helper_info
	{
		public:
			helper_info() {}
			helper_info(std::string f, std::string o, gal::itf::hash_type nhc):
				file_name(f),
				object_name(o),
	       			hc(nhc) {}

			helper_info(helper_info const & h):
				file_name(h.file_name),
				object_name(h.object_name),
	       			hc(h.hc) {}

			template<class Archive> void	serialize(Archive & ar, int v)
			{
				ar & BOOST_SERIALIZATION_NVP(file_name);
				ar & BOOST_SERIALIZATION_NVP(object_name);
				ar & BOOST_SERIALIZATION_NVP(hc);
			}
		public:
			std::string		file_name;
			std::string		object_name;
			gal::itf::hash_type	hc;
	};

	template<class T_, typename... CTOR_ARGS> class helper:
		public std::enable_shared_from_this< helper< T_, CTOR_ARGS... > >
	{
		public:
			typedef T_ T;
			typedef deleter< helper<T> > del;
			typedef std::enable_shared_from_this< helper< T_, CTOR_ARGS... > > estf;
		private:
			helper(helper<T> const & h) {}
		public:
			helper(std::string f, std::string o):
				handle_(0),
				create_(0),
				destroy_(0),
				hi_(f, o, typeid(T).hash_code()) {}

			helper(helper<T>&& h):
				hi_(h.hi_),
				handle_(std::move(h.handle_)),
				create_(std::move(h.create_)),
				destroy_(std::move(h.destroy_)) {}


			void			open() {

				handle_ = dlopen(hi_.file_name.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
					perror(dlerror());
					abort();
				}

				auto name_create = hi_.object_name + "_create";
				auto name_destroy = hi_.object_name + "_destroy";

				create_	= (T* (*)(CTOR_ARGS...))dlsym(handle_, hi_.object_name.c_str());
				if(create_ == NULL) {
					perror(dlerror());
					abort();
				}

				destroy_ = (void (*)(T*))dlsym(handle_, name_destroy.c_str());
				if(destroy_ == NULL) {
					perror(dlerror());
					abort();
				}
			}
			~helper() {
				if(handle_)
					dlclose(handle_);
			}
		public:
			friend class deleter< helper<T> >;

			std::shared_ptr<T>	make_shared(CTOR_ARGS... c)
			{
				std::shared_ptr<T> t(create(c...), del(estf::shared_from_this()));
				return t;
			}
		private:
			T*		create(CTOR_ARGS... c)
			{
				if(!create_) abort();
				return create_(c...);
			}
			void		destroy(T* t)
			{
				if(!destroy_) abort();
				destroy_(t);
			}

		private:
			void*		handle_;
			T*		(*create_)(CTOR_ARGS...);
			void		(*destroy_)(T*);
			helper_info	hi_;
	};
	struct deleter_base
	{
		public:
			deleter_base(helper_info hi): hi_(hi) {}

			helper_info const	getHelperInfo() { return hi_; }
		protected:
			helper_info const	hi_;
	};
	template<typename H> struct deleter
	{
		public:
			typedef typename H::T		T;
			typedef std::shared_ptr< H >	H_s;

			deleter(H_s h):
				_M_helper(h) { assert(h); }

			deleter(deleter<H>&& d):
				_M_helper(std::move(d._M_helper)) {}

			deleter(deleter<H> const & d):
				_M_helper(d._M_helper) {}

			void			operator()(T* t) {
				t->release();
				_M_helper->destroy(t);
			}
		private:
			H_s		_M_helper;
	};
}}

#endif

