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
#include <gal/shared.hpp>
#include <gal/stl/funcmap.hpp>
#include <gal/dll/class_info.hpp>

namespace gal { namespace dll {
	/*
	 * used by deleter to keep helper alive
	 */
	class helper_base:
		public gal::enable_shared_from_this<helper_base>,
		public gal::tmp::Verbosity<gal::dll::helper_base>
	{
	public:
		using gal::enable_shared_from_this<
			gal::dll::helper_base>::shared_from_this;
		using gal::tmp::Verbosity<
			gal::dll::helper_base>::printv;
	};
	template< class B_, template<typename T> class S_ >
	class helper:
		public helper_base,
		private gal::stl::funcmap<B_, S_>
	{
	public:

		typedef B_ B;
		typedef gal::stl::funcmap<B_, S_> FM;

		template<typename T>
		using S = S_<T>;

	private:
		helper(helper<B,S> const & h)
		{}
	public:
		helper(std::string f):
			handle_(0),
			filename_(f)
		{
		}
		helper(helper<B,S>&& h):
			handle_(std::move(h.handle_)),
			filename_(std::move(h.filename_))
		{
		}
		template<class D, typename... ARGS>
		void		add(std::string o)
		{
			//D*   (*pcreate)(ARGS...);
			//void (*pdestroy)(D*);

			//auto hc = typeid(D).hash_code();
	
			if(!handle_) {
				printf("file: %s\n", filename_.c_str());
				printf("handle not open\n");
				abort();
			}

			typedef class_info_destroy_0 CID0;
			typedef class_info<D, ARGS...> CI;
			typedef std::shared_ptr<CI> S_C;

			
			auto lambda_delete = [] (
					std::shared_ptr<CID0> c,
					gal::_release * p)
			{
				assert(c);
				(*c)(p);
			};
			
			//typedef std::function<
			//	void(CI, gal::_release *)> F;
			
			gal::dll::deleter::FUNC func_delete(lambda_delete);

			gal::dll::helper_info hi(filename_, o, typeid(D));

			gal::dll::deleter del(
						shared_from_this(),
						func_delete,
						hi,
						0);

			std::shared_ptr<CI> ci(new CI(o, del));
			ci->open(handle_);

			ci->_M_del._M_class_info = ci;

			// capture by value
			auto lamb = [] (S_C ci, ARGS... args) -> S<B>
			{
		
				//assert(pcreate);
				//D* d = pcreate(args...);
				D* d = (*ci)(args...);
				
				S<D> t(d, ci->_M_del);
				
				return t;
			};
			
			std::function< S<B>(S_C, ARGS...) > f(lamb);

			FM::template add_cd<D, S_C>(f, ci);
		}
		void			open()
		{
			handle_ = dlopen(filename_.c_str(), RTLD_LAZY);
			if(handle_ == NULL) {
				printf("file: %s\n", filename_.c_str());
				perror(dlerror());
				abort();
			}
		}
		~helper() {
			if(handle_)
				dlclose(handle_);
		}
	public:
		template<typename D, typename... ARGS>
		S<D>		make_shared(ARGS... args)
		{
			typedef class_info<D, ARGS...> CI;
			typedef std::shared_ptr<CI> S_C;
	
			printv_func(DEBUG);
		
			size_t h = typeid(D).hash_code();

			auto f = FM::template find_cd<S_C, ARGS...>(h);
			
			//assert(f->_M_f);
			
			S<B> b = (*f)(args...);

			auto d = std::dynamic_pointer_cast<D>(b);
			assert(d);

			return d;
		}
	private:
		void*		handle_;
		std::string	filename_;
	};
}}

#endif

