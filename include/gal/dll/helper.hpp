#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <string>

namespace gal { namespace dll {

	template<class T> class helper {
		public:
			helper(): handle_(0), create_(0), destroy_(0) {}


			void			open(::std::string filename, ::std::string name_class) {

				handle_ = dlopen(filename.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
					perror(dlerror());
					exit(0);
				}

				auto name_create = name_class + "_create";
				auto name_destroy = name_class + "_destroy";


				create_	= (T* (*)())dlsym(handle_, name_create.c_str());
				if(create_ == NULL) {
					perror(dlerror());
					exit(0);
				}

				destroy_ = (void (*)(T*))dlsym(handle_, name_destroy.c_str());
				if(destroy_ == NULL) {
					perror(dlerror());
					exit(0);
				}
			}
			~helper() {
				dlclose(handle_);
			}


			void*		handle_;

			T*		(*create_)();
			void		(*destroy_)(T*);
	};


}}}

#endif

