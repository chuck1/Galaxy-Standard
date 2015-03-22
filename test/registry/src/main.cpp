
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/stl/map.hpp>
#include <gal/registry_object.hpp>

namespace ba = boost::archive;

struct foo: gal::managed_object
{
	virtual void	release()
	{
	}
};

int main()
{
	typedef gal::registry_object R;
	typedef std::shared_ptr<R> S_R;
	
	//S_R r(new R(&gal::managed_object::get_index, &gal::managed_object::set_index));
	S_R r(new R);
	
	typedef std::shared_ptr<foo> S_F;

	S_F f0(new foo);
	S_F f1(new foo);
	S_F f2(new foo);

	r->reg(f0);
	r->reg(f1);
	r->reg(f2);

	gal::object_index i0 = f0->get_index();

	r->get(i0);
}

