#include <stdio.h>

#include <gal/etc/print.hpp>

namespace NS = gal::etc;

void		NS::print(glm::mat4 const & m)
{
				printf("%16f%16f%16f%16f\n%16f%16f%16f%16f\n%16f%16f%16f%16f\n%16f%16f%16f%16f\n",
						m[0][0],m[0][1],m[0][2],m[0][3],
						m[1][0],m[1][1],m[1][2],m[1][3],
						m[2][0],m[2][1],m[2][2],m[2][3],
						m[3][0],m[3][1],m[3][2],m[3][3]);
}
void		NS::print(glm::vec3 const & v)
{
				printf("%16f%16f%16f\n",
						v[0],
						v[1],
						v[2]);
}
void		NS::print(glm::vec4 const & v)
{
				printf("%16f%16f%16f%16f\n",
						v[0],
						v[1],
						v[2],
						v[3]);
}
void		NS::print(glm::quat const & v)
{
				printf("%16f%16f%16f%16f\n",
						v[0],
						v[1],
						v[2],
						v[3]);
}
void		NS::print(gal::math::pose const & v)
{
	NS::print(v.pos_);
	NS::print(v.rot_);
}

