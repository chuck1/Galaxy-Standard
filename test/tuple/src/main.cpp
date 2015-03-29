#include <sstream>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/serialization/serialization.hpp>

namespace ba = boost::archive;

struct foo
{
	template<typename A>
	void serialize(A & a, unsigned int const &)
	{}
};

int main()
{
	std::tuple<foo> t;
	
	std::stringstream ss;

	ba::binary_oarchive ar(ss);

	ar << t;
}

