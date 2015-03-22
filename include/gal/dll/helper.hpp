#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/serialization/nvp.hpp>

#include <gal/typedef.hpp>

#include <gal/decl.hpp>
#include <gal/dll/helper_info.hpp>
#include <gal/dll/deleter.hpp>

#include <gal/stl/funcmap.hpp>

namespace gal { namespace dll {
	/*
	 * used by deleter to keep helper alive
	 */
	class helper_base:
		public std::enable_shared_from_this< helper_base >
	{
	public:
		using std::enable_shared_from_this< helper_base >::shared_from_this;
	};
	template< class B_, template<typename T> class S_ >
	class helper:
		public gal::tmp::Verbosity< gal::dll::helper< B_, S_ > >,
		public helper_base,
		private gal::stl::funcmap<B_, S_>
	{
		public:
			using gal::tmp::Verbosity< gal::dll::helper< B_, S_ > >::printv;
			typedef B_ B;
			template<typename T> using S = S_<T>;
			typedef gal::stl::funcmap<B_, S_> FM;
		private:
			helper(helper<B,S> const & h) {}
		public:
			helper(std::string f):
				handle_(0),
				filename_(f)
			{
			}
			helper(helper<B,S>&& h):
				/*hi_(h.hi_),*/
				handle_(std::move(h.handle_))
				//create_(std::move(h.create_)),
				//destroy_(std::move(h.destroy_))
			{
			}
		
			template<class D, typename... ARGS>
			void		add(std::string o)
			{
				D*   (*pcreate)(ARGS...);
				void (*pdestroy)(D*);
	
				//auto hc = typeid(D).hash_code();
		
				if(!handle_) {
					printf("file: %s\n", filename_.c_str());
					printf("handle not open\n");
					abort();
				}

				auto name_create = o + "_create";
				auto name_destroy = o + "_destroy";

				pcreate = (D* (*)(ARGS...))dlsym(handle_, name_create.c_str());
				if(pcreate == NULL) {
					printf("file: %s\n", filename_.c_str());
					perror(dlerror());
					abort();
				}

				pdestroy = (void (*)(D*))dlsym(handle_, name_destroy.c_str());
				if(pdestroy == NULL) {
					printf("file: %s\n", filename_.c_str());
					perror(dlerror());
					abort();
				}
	
				// capture by value
				auto lambda_delete = [=] (gal::_release * p)
				{
					D* d = dynamic_cast<D*>(p);
					assert(d);
					assert(pdestroy);
					pdestroy(d);
				};

				std::function< void(gal::_release *) > func_delete(lambda_delete);

				gal::dll::helper_info hi(filename_, o, typeid(D));

				gal::dll::deleter del(shared_from_this(), func_delete, hi);

				// capture by value
				auto lamb = [=] (ARGS... args) -> S<B>
				{
					assert(pcreate);
					D* d = pcreate(args...);
					
					S<D> t(d,del);
					
					return t;
				};
			
				std::function< S<B>(ARGS...) > f(lamb);

				FM::template add<D>(f);
			}
			void			open()
			{
				handle_ = dlopen(filename_.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
					printf("file: %s\n", filename_.c_str());
					perror(dlerror());
					abort();
				}


				/*
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
				*/
			}
			~helper() {
				if(handle_)
					dlclose(handle_);
			}
		public:
			//friend class gal::dll::deleter;

			template<typename D, typename... ARGS>
			S<D>	make_shared(ARGS... args)
			{
				printv_func(DEBUG);

				auto hc = typeid(D).hash_code();

				auto f = FM::template find<ARGS...>(hc);
				
				assert(f->f_);

				S<B> b = f->f_(args...);

				auto d = std::dynamic_pointer_cast<D>(b);
				assert(d);

				return d;
			}
			/*
			td::shared_ptr<T>	make_shared(CTOR_ARGS... c)
			{
				td::shared_ptr<T> t(
						create(c...),
						gal::dll::deleter(estf::shared_from_this(), hi_)
						);
				return t;
			}
			*/
		private:
			/*
			B*		create(CTOR_ARGS... c)
			{
				if(!create_) abort();
				return create_(c...);
			}
			virtual void	destroy(gal::managed_object* p)
			{
				T* t = dynamic_cast<T*>(p);
				destroy(t);
			}
			void		destroy(T* t)
			{
				if(!destroy_) abort();
				destroy_(t);
			}
			*/
		private:
			void*		handle_;
			//T*		(*create_)(CTOR_ARGS...);
			//void		(*destroy_)(T*);
			std::string	filename_;
			//helper_info	hi_;
	};
}}

#endif

