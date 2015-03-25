
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/registry_object.hpp>
#include <gal/registry_process.hpp>
#include <gal/unique_ptr.hpp>

#include <gal/stl/map.hpp>

namespace ba = boost::archive;

struct bar:
	gal::registry_object
	//gal::managed_object
{
	virtual void	release()
	{
	}
};

struct foo: gal::managed_object
{
	virtual void	release()
	{
	}

	void	a() {}
	void	b() const {}
};

int main()
{
	typedef gal::stl::map<foo, gal::unique_ptr<foo>> M;

	typedef std::shared_ptr<bar> S_B;
	typedef std::shared_ptr<M> S_M;
	
	std::shared_ptr<gal::registry_process> rp(new gal::registry_process);
	rp->init();
	
	S_B b(new bar);

	rp->reg(b);

	b->init();
	
	S_M pm(new M);
	
	M & m = *pm;

	m.init(b.get());

	m.insert(M::S(new foo));
	m.insert(M::S(new foo));
	m.insert(M::S(new foo));
	
	m.begin();
	m.end();
	m.cbegin();
	m.cend();
	m.random();
	m.size();
	m.erase(gal::object_index(0,0));
	m.empty();

	try {
		m.find(gal::object_index(0,0));
	} catch(std::exception& e) {
		printf("%s\n", e.what());
	}

	m.change_process_index(1,2);


	m.front();

	m.for_each([](M::S & s){ s->a(); });
	m.for_each([](M::S & s){ s->b(); });

	m.for_each([](M::T & t){ t.a(); });
	//m.for_each([](M::T const & t){ t.a(); });
	m.for_each([](M::T & t){ t.b(); });
	m.for_each([](M::T const & t){ t.b(); });

	m.clear();

	return 0;
}

