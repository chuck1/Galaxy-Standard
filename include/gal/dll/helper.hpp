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

namespace gal { namespace dll {
	class class_info_destroy_0
	{
	public:
		virtual void	operator()(gal::_release *) = 0;
	};
	template<class D>
	class class_info_destroy:
		public class_info_destroy_0
	{
	public:
		typedef void(*PD)(D*);
		class_info_destroy(std::string n):
			_M_name(n),
			_M_pd(NULL)
		{}
		virtual void	operator()(gal::_release * r)
		{
			D* d = dynamic_cast<D*>(r);
			if(!d) {
				abort();
			}
			operator()(d);
		}
		void		open_destroy(void* handle)
		{
			auto name_d = _M_name + "_destroy";

			_M_pd = (PD)dlsym(
					handle,
					name_d.c_str());
			
			if(_M_pd == NULL) {
				//printf("file: %s\n",
				//	filename_.c_str());
				perror(dlerror());
				abort();
			}
		}
		void		operator()(D* d)
		{
			if(_M_pd == NULL) abort();
			_M_pd(d);
		}
	protected:
		std::string	_M_name;
		PD		_M_pd;
	};
	template<class D, typename... ARGS>
	class class_info: public class_info_destroy<D>
	{
	public:
		typedef D*(*PC)(ARGS...);

		using class_info_destroy<D>::open_destroy;
		using class_info_destroy<D>::_M_name;

		class_info(std::string n):
			class_info_destroy<D>(n),
			_M_pc(NULL)
		{}
		void		open(void* handle)
		{
			open_destroy(handle);

			auto name_c = _M_name + "_create";

			_M_pc = (PC)dlsym(
					handle,
					name_c.c_str());

			if(_M_pc == NULL) {
				//printf("file: %s\n",
				//	filename_.c_str());
				perror(dlerror());
				abort();
			}
		}
		D*		operator()(ARGS... a)
		{
			if(_M_pc == NULL) abort();
			return _M_pc(a...);
		}
	private:
		PC		_M_pc;
	};
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

			std::shared_ptr<CI> ci(new CI(o));
			ci->open(handle_);
			
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
					hi);

			// capture by value
			auto lamb = [=] (CI ci, ARGS... args) -> S<B>
			{
				//assert(pcreate);
				//D* d = pcreate(args...);
				D* d = ci(args...);
				
				S<D> t(d,del);
				
				return t;
			};
				
			std::function< S<B>(CI, ARGS...) > f(lamb);

			FM::template add_cd<D, CI>(f, ci);
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
			printv_func(DEBUG);

			typedef class_info<D, ARGS...> CI;
			
			size_t h = typeid(D).hash_code();

			auto f = FM::template find_cd<CI, ARGS...>(h);
			
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

