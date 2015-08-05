#ifndef GAL_STD_PARENT_HPP
#define GAL_STD_PARENT_HPP

#include <gal/stl/map.hpp>
#include <gal/managed_object.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/stl/child.hpp>

namespace gal { namespace stl {
	class parent_base:
		virtual public gal::tmp::Verbosity<gal::stl::parent_base>
	{
	public:
		using gal::tmp::Verbosity<gal::stl::parent_base>::printv;
	};
	template< typename T, typename S_ = std::shared_ptr<T> >
	class parent:
		virtual public gal::stl::parent_base,
		virtual public gal::managed_object
	{
	public:
		using gal::tmp::Verbosity<gal::stl::parent_base>::printv;
		friend class boost::serialization::access;
		//typedef std::shared_ptr<T>		S;
		typedef S_				S;
		typedef gal::stl::map<T, S_>		MAP;
		typedef typename MAP::W			W;
		typedef std::shared_ptr<MAP>		MAP_SHARED;
		typedef typename MAP::iterator		ITER;
		typedef typename MAP::FILTER_FUNC	FILTER_FUNC;
		parent()
		{
		}
		void			init(gal::managed_object * parent)
		{
			assert_map();
		}
		void			register_all(gal::registry_object * r)
		{
			assert_map();
			auto l = [&] (S & s) {
				s->register_all(r);
			};
			map_->for_each(l);
		}
		void			change_process_index(
				gal::process_index p0,
				gal::process_index p1)
		{
			assert_map();
			map_->change_process_index(p0, p1);
		}
		void			insert(S && s)
		{
			assert(map_);
			map_->insert(std::move(s));
		}
		W			get(gal::object_index i)
		{
			assert(map_);
			return map_->find(i);
		}
		void			erase(gal::object_index i)
		{
			auto me = std::dynamic_pointer_cast< gal::stl::parent< T > >(shared_from_this());
			boost::thread t(boost::bind(
					&gal::stl::parent< T >::thread_erase,
					me,
					i
					));
			
			t.detach();
		}
		void			clear()
		{
			if(map_) //assert(map_);
				map_->clear();
		}
		W			front(FILTER_FUNC func = FILTER_FUNC())
		{
			assert(map_);
			return map_->front(func);
		}
		W			random()
		{
			assert(map_);
			return map_->random();
		}
		ITER			begin()
		{
			assert(map_);
			return map_->begin();
		}
		ITER			end()
		{
			assert(map_);
			return map_->end();
		}
		unsigned int		size()
		{
			assert_map();
			return map_->size();
		}
		bool			empty()
		{
			if(map_)
				return map_->empty();

			return true;
		}
		void			for_each(std::function<void(S &)> const & f)
		{
			assert_map();
			map_->for_each(f);
		}
/*		void			for_each(std::function<void(S const &)> const & f)
		{
			assert_map();
			map_->for_each(f);
		}
		*/
		void			for_each_int(std::function<int(S &)> const & f)
		{
			assert_map();
			map_->for_each_int(f);
		}
	
	private:
		void			assert_map()
		{
			if(!map_) {
				map_.reset(new MAP);
				map_->gal::verbosity_base::init(get_vr());
				map_->init(get_registry());
			}
		}

		template<typename ARCHIVE>
		void			load(
				ARCHIVE & ar,
				unsigned int const & version)
		{
			printv_func(DEBUG);
			assert_map();
			ar & boost::serialization::make_nvp("map", *map_);

			// set the parent of each object
			auto p = dynamic_cast<typename T::parent_t *>(this);

			auto l = [&] (T & t) {
				try {
					t.init(p);
				} catch(gal::stl::child_util::exception_parent_is_null & e) {
					// if 
					//   initialization fails because an ancestor of
					//   t has a null parent
					// then
					//   not an error
				}
			};
			
			map_->for_each(l);
		}
		template<typename ARCHIVE>
		void			save(
				ARCHIVE & ar,
				unsigned int const & version) const
		{
			printv_func(DEBUG);
			//assert_map();
			assert(map_);
			ar & boost::serialization::make_nvp("map", *map_);
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER();

		void			thread_erase(gal::object_index i)
		{
			map_->erase(i);
		}
		MAP_SHARED		map_;
	};
}}

#endif




