#ifndef NEBULA_CORE_POSE_HPP
#define NEBULA_CORE_POSE_HPP

#include <glm/gtc/matrix_transform.hpp>

#include <gal/math/serialization/glm.hpp>

namespace gal { namespace math {
	/** @brief %pose
	*
	*/
	class pose {
		public:
			pose();
			pose(gal::math::pose const & rhs);
			pose(gal::math::pose&& rhs);
			pose(glm::vec3 p, glm::quat q);
			pose(glm::vec3 p);
			pose(glm::quat q);
			pose&		operator=(gal::math::pose const & rhs);
			pose		operator*(gal::math::pose const & rhs) const;
			template<typename Archive> void		serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("pos", pos_);
				ar & boost::serialization::make_nvp("rot", rot_);
			}
			glm::mat4		mat4_cast() const;
			glm::vec3		pos_;
			glm::quat		rot_;
	};
}}

#endif


