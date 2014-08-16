#ifndef NEBULA_UTIL_FUNCMAP_HPP
#define NEBULA_UTIL_FUNCMAP_HPP

#include <map>
#include <memory>

#include <gal/std/decl.hpp>
#include <gal/std/typedef.hpp>

namespace sp = std;

namespace gal {
	namespace std {
		/** @brief funcmap
		 *
		 * A map containing @c ::std::function objects with arbitrary signatures
		 * Motivation: See factory and Initializer classes
		 */
		template<typename T> class funcmap {
			private:
				typedef sp::shared_ptr<T>						shared_type;
				/** */
				struct __base_function {
					virtual ~__base_function() {}
				};
				/** */
				template<class... A> struct __function: __base_function {
					/** */
					__function(::std::function< shared_type(A...) > f): f_(f) {}
					/** */
					::std::function< shared_type(A...) >		f_;
				};
				typedef ::std::map< long int, ::std::shared_ptr<__base_function> >	map_type;
				/** */
				struct invalid_key: ::std::exception {
					char const *	what() {
						return "invalid key";
					}
				};
				/** */
				struct invalid_args: ::std::exception {
					char const *	what() {
						return "invalid args";
					}
				};

			public:
				funcmap() {}
				virtual ~funcmap() {}
				/** */
				template<typename... Args> void						add(
						gal::std::hash_type hash_code,
						::std::function< shared_type(Args...)> f)
				{
					::std::shared_ptr<__base_function> b(new __function< Args...>(f));

					//map_.emplace(hash_code, b);
					map_[hash_code] = b;
				}
				/** */
				template<typename... Args> sp::shared_ptr< __function< Args... > >		find(
						gal::std::hash_type hash_code)
				{
					auto it = map_.find(hash_code);

					if(it == map_.cend()) throw invalid_key();

					//::std::shared_ptr< __function<return_type, Args...> >
					auto f = ::std::dynamic_pointer_cast< __function< Args... > >(it->second);

					if(!f) throw invalid_args();

					return f;
				}
			private:
				map_type         	map_;

		};
	}
}

#endif





