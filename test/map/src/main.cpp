
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/stl/map.hpp>

namespace ba = boost::archive;

struct foo: gal::itf::shared
{
	virtual void	release()
	{
	}
};

int main()
{
	typedef gal::stl::map<foo> M;
	
	M m;
	
	m.insert(M::S(new foo));
	m.insert(M::S(new foo));
	m.insert(M::S(new foo));
	
	m.begin();
	m.end();
	m.cbegin();
	m.cend();
	m.random();
	m.size();
	m.erase(0);
	m.empty();
	m.find(0);
	m.front();
	m.clear();

	return 0;
}

