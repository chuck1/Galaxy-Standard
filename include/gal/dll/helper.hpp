#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>

#include <gal/dll/helper_info.hpp>
#include <gal/dll/deleter.hpp>

#include <gal/stl/funcmap.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {

	class helper_base
	{
		public:
			virtual void		destroy(gal::itf::shared* v) = 0;
	};

	template<class D>
	class deleter1
	{
	public:
		deleter1(void (*pdestroy)(D*)):
			_M_pdestroy(pdestroy)
		{
		}
		void		operator()(gal::itf::shared* p)
		{
			p->release();
			assert(_M_pdestroy);
			D* d = dynamic_cast<D*>(p);
			assert(d);
			_M_pdestroy(d);
		}
	private:
		void	(*_M_pdestroy)(D*);
	};

	/*
	 * B is the base type for the funcmap
	 */
	template<class B_> class helper:
		public std::enable_shared_from_this< helper<B_> >,
		private gal::stl::funcmap<B_>
	{
		public:
			typedef B_ B;
			typedef std::enable_shared_from_this< helper< B > > estf;
		private:
			helper(helper<B> const & h) {}
		public:
			helper(std::string f):
				handle_(0),
				hi_(f, typeid(B)) {}

			helper(helper<B>&& h):
				hi_(h.hi_),
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
			
				if(!handle_) {
					printf("handle not open\n");
					abort();
				}

				auto name_create = o + "_create";
				auto name_destroy = o + "_destroy";

				pcreate = (D* (*)(ARGS...))dlsym(handle_, name_create.c_str());
				if(pcreate == NULL) {
					perror(dlerror());
					abort();
				}

				pdestroy = (void (*)(D*))dlsym(handle_, name_destroy.c_str());
				if(pdestroy == NULL) {
					perror(dlerror());
					abort();
				}
	
				auto lamb = [&] (ARGS... args)
				{
					std::shared_ptr<D> t(
							pcreate(args...),
							gal::dll::deleter1<D>(pdestroy)
							);
					return t;
				};
			
				std::function< std::shared_ptr<B>(ARGS...) > f(lamb);

				gal::stl::funcmap<B>::template add<D>(f);
			}
			void			open()
			{
				std::string filename = hi_.file_name;
				
				handle_ = dlopen(filename.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
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
			friend class gal::dll::deleter;

			template<typename D, typename... ARGS>
			std::shared_ptr<D>	make_shared(ARGS... args)
			{
				auto hc = typeid(D).hash_code();

				auto f = gal::stl::funcmap<B>::template find<ARGS...>(hc);
				
				assert(f->f_);

				std::shared_ptr<B> b = f->f_(args...);

				auto d = std::dynamic_pointer_cast<D>(b);
				assert(d);

				return d;
			}
			/*
			std::shared_ptr<T>	make_shared(CTOR_ARGS... c)
			{
				std::shared_ptr<T> t(
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
			virtual void	destroy(gal::itf::shared* p)
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
			helper_info	hi_;
	};
}}

#endif

