#ifndef NEBULA_UTIL_FUNCMAP_HPP
#define NEBULA_UTIL_FUNCMAP_HPP

#include <map>
#include <memory>
#include <iostream>

#include <gal/decl.hpp>
#include <gal/itf/typedef.hpp>
#include <gal/stl/helper.hpp>

namespace gal { namespace stl {
	/** @brief funcmap
	 *
	 * A map containing @c ::std::function objects with arbitrary signatures
	 * Motivation: See factory and Initializer classes
	 *
	 * uses std::map to store functions, key is the hash code of the type being constructed
	 */
	template<typename T, template<typename T2> class S_ = std::shared_ptr>
	class funcmap
	{
		private:
			struct __base_function
			{
				virtual ~__base_function() {}
				virtual char const *	signature() = 0;
			};

			typedef S_<T> shared_type;
			typedef std::map< long int, S_<__base_function> > map_type;
			
			template<class... A>
			struct __function: __base_function
			{
				__function(std::function< shared_type(A...) > f, const char * s):
					f_(f),
					_M_signature(s)
				{
				}
				virtual char const *	signature()
				{
					return _M_signature;
				}
				std::function< shared_type(A...) >		f_;
				const char *					_M_signature;
			};
			/**
			 * exception
			 */
			struct invalid_key: std::exception {
				virtual char const *	what() {
					return "funcmap: invalid key";
				}
			};
			/*
			 * exception
			 */
			struct invalid_args: std::exception {
				virtual char const *	what() {
					return "funcmap: invalid args";
				}
			};
		public:
			funcmap() {}
			virtual ~funcmap() {}
			/** */
			template<typename D, typename... Args>
			void			add(
					std::function< shared_type(Args...) > f)
			{
				typedef __function< Args... > func_t;

				gal::itf::hash_type hash_code = typeid(D).hash_code();
				
				S_<__base_function> b(new func_t(f, __PRETTY_FUNCTION__));
				
				//map_.emplace(hash_code, b);
				std::pair<typename map_type::iterator, bool> p = map_.insert(std::make_pair(hash_code, b));
				
				if(p.second)
				{
					/*
					std::cout << "inserted:" << std::endl;
					std::cout << "hash_code " << hash_code << std::endl;
					std::cout << "func_t    " << typeid(func_t).name() << std::endl;
					std::cout << typeid(f).name() << std::endl;
					*/
				}
				else
				{
					std::cout << "not inserted:" << std::endl;
					std::cout << "hash_code " << hash_code << std::endl;
					std::cout << "func_t    " << typeid(func_t).name() << std::endl;
					std::cout << typeid(f).name() << std::endl;
					throw 0;
				}
			}
			void						list()
			{
				printf("funcmap entries:\n");
				for(auto p : map_) {
					printf("%16li %s\n", p.first, p.second->signature());
				}
			}
			/** */
			template<typename... Args>
			S_< __function< Args... > >	find(
					gal::itf::hash_type hash_code)
			{
				typedef __function< Args... > func_t;
				
				auto it = map_.find(hash_code);

				if(it == map_.cend())
				{	
					printf("signature not found in funcmap\n");
					pass1(printf("%s\n", typeid(Args).name())...);
					std::cout
						<< "T    = " << typeid(T).name() << std::endl
						<< "hash = " << hash_code << std::endl;
					
					list();

					throw invalid_key();
				}
				
				//::td::shared_ptr< __function<return_type, Args...> >
				auto f = std::dynamic_pointer_cast< __function< Args... > >(it->second);
				
				if(!f)
				{
					printf("invalid args\n");
					pass1(printf("%s\n", typeid(Args).name())...);
					std::cout
						<< "func = " << typeid(func_t).name() << std::endl
						<< "T    = " << typeid(T).name() << std::endl
						<< "hash = " << hash_code << std::endl;

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





