#ifndef GAL_ETC_PRINT_HPP
#define GAL_ETC_PRINT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <gal/math/pose.hpp>

namespace gal { namespace etc {
	void		print(glm::vec3 const & v);
	void		print(glm::vec4 const & v);
	void		print(glm::quat const & v);
	void		print(glm::mat4 const & v);
	void		print(gal::math::pose const & v);
}}

#endif
