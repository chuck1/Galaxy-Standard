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

	/*
	 * used by deleter to keep helper alive
	 */
	class helper_base:
		public std::enable_shared_from_this< helper_base >
	{
	};

	/*
	template<typename D>
	class deleter1
	{
	public:
		deleter1(std::shared_ptr<gal::dll::helper_base> hb, void (*pdestroy)(D*)):
			_M_helper(hb),
			_M_pdestroy(pdestroy)
		{
		}
		virtual ~deleter1()
		{
		}
		deleter1(deleter1<D>&& d):
			_M_helper(std::move(d._M_helper)),
			_M_pdestroy(std::move(d._M_pdestroy))
		{
		}
		deleter1(deleter1<D> const & d):
			_M_helper(d._M_helper),
			_M_pdestroy(d._M_pdestroy)
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
		*
		 * keep the helper alive (the the so open) at least until all objects are destroyed
		 *
		std::shared_ptr< gal::dll::helper_base >	_M_helper;
		void						(*_M_pdestroy)(D*);
	};
	*/

	/*
	 * B is the base type for the funcmap
	 */
	template<class B_> class helper:
		public helper_base,
		private gal::stl::funcmap<B_>
	{
		public:
			typedef B_ B;
			typedef std::enable_shared_from_this< helper_base > estf;
		private:
			helper(helper<B> const & h) {}
		public:
			helper(std::string f):
				handle_(0),
				filename_(f)
			{
			}
			helper(helper<B>&& h):
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
				auto lambda_delete = [=] (gal::itf::shared* p)
				{
					D* d = dynamic_cast<D*>(p);
					assert(d);
					assert(pdestroy);
					pdestroy(d);
				};

				std::function< void(gal::itf::shared*) > func_delete(lambda_delete);

				gal::dll::helper_info hi(filename_, o, typeid(D));

				gal::dll::deleter del(estf::shared_from_this(), func_delete, hi);

				// capture by value
				auto lamb = [=] (ARGS... args) -> std::shared_ptr<B>
				{
					assert(pcreate);
					D* d = pcreate(args...);
					
					std::shared_ptr<D> t(d,del);
					
					return t;
				};
			
				std::function< std::shared_ptr<B>(ARGS...) > f(lamb);

				gal::stl::funcmap<B>::template add<D>(f);
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
			std::string	filename_;
			//helper_info	hi_;
	};
}}

#endif

