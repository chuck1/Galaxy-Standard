#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <cassert>
#include <string>

namespace gal { namespace dll {

	template<class T_, typename... CTOR_ARGS> class helper {
		public:
			typedef T_ T;
		private:
			helper(helper<T> const & h) {}
		public:
			helper(): handle_(0), create_(0), destroy_(0) {}

			helper(helper<T>&& h):
				handle_(std::move(h.handle_)),
				create_(std::move(h.create_)),
				destroy_(std::move(h.destroy_)) {}


			void			open(std::string filename, std::string name_class) {

				handle_ = dlopen(filename.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
					perror(dlerror());
					abort();
				}

				auto name_create = name_class + "_create";
				auto name_destroy = name_class + "_destroy";


				create_	= (T* (*)(CTOR_ARGS...))dlsym(handle_, name_create.c_str());
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
	};

	template<typename H> struct deleter
	{
		public:
			typedef typename H::T		T;
			typedef std::shared_ptr< H >	H_s;
			
			deleter(H_s h): _M_helper(h) { assert(h); }
			
			deleter(deleter<H>&& d): _M_helper(std::move(d._M_helper)) {}
			
			deleter(deleter<H> const & d): _M_helper(d._M_helper) {}
			
			void			operator()(T* t) {
				t->release();
				_M_helper->destroy(t);
			}
		private:
			H_s		_M_helper;
	};
}}

#endif

