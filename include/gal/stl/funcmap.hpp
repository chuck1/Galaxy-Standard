#ifndef NEBULA_UTIL_FUNCMAP_HPP
#define NEBULA_UTIL_FUNCMAP_HPP

#include <map>
#include <memory>
#include <iostream>

#include <gal/decl.hpp>
#include <gal/typedef.hpp>
#include <gal/stl/helper.hpp>

namespace gal { namespace stl {

	struct invalid_key: std::exception
	{
		virtual char const *	what() {
			return "funcmap: invalid key";
		}
	};
	struct invalid_args: std::exception
	{
		virtual char const *	what() {
			return "funcmap: invalid args";
		}
	};
	struct void_function: std::exception
	{
		virtual char const *	what() {
			return "funcmap: void function";
		}
	};

	class __base_function
	{
	public:
		
		virtual ~__base_function() {}
		__base_function(const char * s):
			_M_signature(s)
		{}
		char const *		signature()
		{
			return _M_signature;
		}
		const char *		_M_signature;
	};
	/**
	 * A... arguments to creation function supplied by user
	 */
	template<class T, class... A>
	class __function:
		public __base_function
	{
	public:
		typedef std::shared_ptr<T>	shared_type;
		typedef std::function<shared_type(A...)> func_type;
		__function(
				std::function< shared_type(A...) > f,
				const char * s):
			__base_function(s),
			f_(f)
		{
		}
		shared_type		operator()(A... a)
		{
			if(f_) {
				return f_(a...);
			}
			throw void_function();
		}
	private:
		func_type		f_;
	};
	template<typename T, typename CD, class... A>
	class __function_common_data:
		public __base_function
	{
	public:
		typedef std::shared_ptr<T>	shared_type;
		typedef std::function<shared_type(CD, A...)>
			func_type;

		__function_common_data(
				func_type f,
				const char * s,
				CD cd):
			__base_function(s),
			_M_f(f),
			_M_cd(cd)
		{
		}
		shared_type		operator()(A... a)
		{
			if(_M_f) {
				return _M_f(_M_cd, a...);
			}
			throw void_function();
		}
	private:
		func_type		_M_f;
		CD			_M_cd;
	};
	/** @brief funcmap
	 *
	 * A map containing @c ::std::function objects with
	 * arbitrary signatures
	 * Motivation: See factory and Initializer classes
	 *
	 * uses std::map to store functions, key is the hash code
	 * of the type being constructed
	 */
	template<
		typename T,
		template<typename T2> class S_ = std::shared_ptr>
	class funcmap
	{
	private:
		typedef S_<T>		shared_type;


		typedef std::shared_ptr<__base_function>	S_F;
		typedef std::map<long int, S_F>			map_type;
		typedef typename map_type::iterator		iter;
	public:
		funcmap() {}
		virtual ~funcmap() {}
		void			print_error(
				std::string s0,
				size_t h,
				std::string s1,
				std::string s2)
		{
			printf(
					"%s:\n"
					"\thash code:%i\n"
					"\tfunc_t    %s\n"
					"\tf:        %s\n",
					s0.c_str(),
					h,
					s1.c_str(),
					s2.c_str()
					);

		}
		template<typename D, typename... Args>
		void			add(
				std::function< shared_type(Args...) > f)
		{
			typedef __function<T, Args...> func_t;

			S_F b(new func_t(f, __PRETTY_FUNCTION__));
			
			std::pair<iter, bool> p = map_.insert(
					std::make_pair(
						typeid(D).hash_code(),
						b));
			
			if(p.second) {
				if(0) {
					print_error(
						"inserted",
						typeid(D).hash_code(),
						typeid(func_t).name(),
						typeid(f).name());
				}
			}
			else
			{
				print_error(
					"not inserted",
					typeid(D).hash_code(),
					typeid(func_t).name(),
					typeid(f).name());
				abort();
			}
		}
		template<typename D, typename CD, typename... Args>
		void			add_cd(
				std::function<shared_type(CD, Args...)> f,
				CD cd)
		{
			typedef __function_common_data<T, CD, Args...>
				func_t;

			S_F b(new func_t(f, __PRETTY_FUNCTION__, cd));
	
			auto h = typeid(D).hash_code();

			std::pair<iter, bool> p = map_.insert(
					std::make_pair(
						h, b));
			
			if(p.second)
			{
				if(0) {
					print_error(
						"inserted",
						typeid(D).hash_code(),
						typeid(func_t).name(),
						typeid(f).name());
				}
			}
			else
			{
				print_error(
					"not inserted",
					typeid(D).hash_code(),
					typeid(func_t).name(),
					typeid(f).name());
				abort();
			}
		}
		void			list()
		{
			printf("funcmap entries:\n");
			for(auto p : map_) {
				printf("%16li %s\n",
						p.first,
						p.second->signature());
			}
		}
		/** */
		template<typename... A>
		void	print_error_info(const char * s, gal::hash_type h)
		{
			printf("%s\n", s);

			printf("Args:\n");

			pass1(printf("\t%s\n", typeid(A).name())...);
			
			printf(
					"T:   %32s\n"
					"hash:%32i\n",
					typeid(T).name(),
					h);
		}
		template<typename... Args>
		std::shared_ptr< __function<T, Args...> >
		find(
				gal::hash_type h)
		{
			typedef __function<Args...> func_t;
			
			auto it = map_.find(h);

			if(it == map_.cend()) {
				print_error_info<Args...>(
						"signature not found "
						"in funcmap",
						h);
				
				list();

				throw invalid_key();
			}
			
			auto f = std::dynamic_pointer_cast<func_t>(it->second);
			
			if(!f) {
				print_error_info<Args...>(
						"invalid args",
						h);

				list();

				throw invalid_args();
			}

			return f;
		}
		template<typename CD, typename... A>
		std::shared_ptr< __function_common_data<T, CD, A...> >
		find_cd(
				size_t h)
		{
			typedef __function_common_data<T, CD, A...> func_t;
			
			auto it = map_.find(h);

			if(it == map_.cend()) {
				print_error_info<A...>(
						"signature not found "
						"in funcmap",
						h);
				
				list();

				throw invalid_key();
			}
			
			auto f = std::dynamic_pointer_cast<func_t>(
					it->second);
			
			if(!f) {
				print_error_info<A...>(
						"invalid args",
						h);

				list();

				throw invalid_args();
			}

			return f;
		}
	private:
		map_type         	map_;
	};
}}

#endif





