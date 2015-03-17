
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/itf/registry.hpp>

#include <gal/stl/map.hpp>

namespace ba = boost::archive;

struct bar:
	gal::itf::registry,
	gal::itf::shared
{
	virtual void	release()
	{
	}
};

struct foo: gal::itf::shared
{
	virtual void	release()
	{
	}

	void	a() {}
	void	b() const {}
};

int main()
{
	typedef gal::stl::map<foo> M;

	typedef std::shared_ptr<bar> S_B;
	typedef std::shared_ptr<M> S_M;

	S_B b(new bar);
	b->_M_p_get_index = &gal::itf::shared::get_index;
	b->_M_p_set_index = &gal::itf::shared::set_index;

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
	m.erase(0);
	m.empty();

	try {
		m.find(0);
	} catch(std::exception& e) {
		printf("%s\n", e.what());
	}


	m.front();
	m.clear();

	m.for_each([](M::S & s){ s->a(); });
	m.for_each([](M::S & s){ s->b(); });

	m.for_each([](M::T & t){ t.a(); });
	//m.for_each([](M::T const & t){ t.a(); });
	m.for_each([](M::T & t){ t.b(); });
	m.for_each([](M::T const & t){ t.b(); });

	return 0;
}

