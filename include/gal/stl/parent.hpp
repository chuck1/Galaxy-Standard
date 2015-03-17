#ifndef GAL_STD_PARENT_HPP
#define GAL_STD_PARENT_HPP

#include <gal/stl/map.hpp>
#include <gal/itf/shared.hpp>
#include <gal/stl/wrapper.hpp>

namespace gal { namespace stl {
	template< typename T, typename S_ = std::shared_ptr<T> >
	class parent:
		virtual public gal::itf::shared,
		virtual public gal::tmp::Verbosity< gal::stl::parent<T,S_> >
	{
	public:
		friend class boost::serialization::access;
		using gal::tmp::Verbosity< gal::stl::parent<T,S_> >::printv;
		//typedef std::shared_ptr<T>		S;
		typedef S_				S;
		typedef gal::stl::map<T, S_>		MAP;
		typedef std::shared_ptr<MAP>		MAP_SHARED;
		typedef typename MAP::iterator		ITER;
		typedef typename MAP::FILTER_FUNC	FILTER_FUNC;
		parent()
		{
		}
		void			init(gal::itf::shared * const & parent)
		{
			assert_map();
		}
		void			insert(S && s)
		{
			assert(map_);
			map_->insert(std::move(s));
		}
		S			get(gal::itf::index_type i)
		{
			assert(map_);
			return map_->find(i);
		}
		void			erase(gal::itf::index_type i)
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
		S			front(FILTER_FUNC func = FILTER_FUNC())
		{
			assert(map_);
			return map_->front(func);
		}
		S			random()
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
		void			for_each(std::function<void(S)> const & f)
		{
			assert_map();
			map_->for_each(f);
		}
		void			for_each_int(std::function<int(S)> const & f)
		{
			assert_map();
			map_->for_each_int(f);
		}
	
	private:
		void			assert_map()
		{
			if(!map_) {
				map_.reset(new MAP);
				map_->init(this);
			}
		}
		template<typename ARCHIVE>
		void			serialize(
				ARCHIVE & ar,
				unsigned int const & version)
		{
			printv_func(DEBUG);
			assert_map();
			ar & boost::serialization::make_nvp("map", *map_);
		}
		void			thread_erase(gal::itf::index_type i)
		{
			map_->erase(i);
		}
		MAP_SHARED		map_;
	};
}}

#endif




