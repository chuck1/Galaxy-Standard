#include <gal/std/timestep.hpp>

gal::std::timestep::timestep():
	time(0.0),
	last(0.0),
	dt(0.0),
	frame(0)
{}
void		gal::std::timestep::step(double ntime) {

	time = ntime;
	dt = time - last;
	last = time;
	frame++;

}

