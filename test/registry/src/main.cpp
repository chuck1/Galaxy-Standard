
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/stl/map.hpp>
#include <gal/itf/registry.hpp>

namespace ba = boost::archive;

struct foo: gal::itf::shared
{
	virtual void	release()
	{
	}
};

int main()
{
	typedef gal::itf::registry R;
	typedef std::shared_ptr<R> S_R;
	
	//S_R r(new R(&gal::itf::shared::get_index, &gal::itf::shared::set_index));
	S_R r(new R);
	
	typedef std::shared_ptr<foo> S_F;

	S_F f0(new foo);
	S_F f1(new foo);
	S_F f2(new foo);

	r->reg(f0);
	r->reg(f1);
	r->reg(f2);
	
	r->get(0);
}
