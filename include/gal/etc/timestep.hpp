#ifndef NEBULA_CORE_TIME_STEP_HPP
#define NEBULA_CORE_TIME_STEP_HPP

namespace gal { namespace etc {
	class timestep
	{
		public:
			timestep();
			void			step(double time);

			double			time;
			double			last;
			double			dt;
			unsigned int		frame;
	};
}
}

#endif
