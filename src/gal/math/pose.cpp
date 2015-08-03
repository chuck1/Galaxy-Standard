
#include <gal/math/pose.hpp>

gal::math::pose::pose():
	pos_(0.0,0.0,0.0)
{};
gal::math::pose::pose(gal::math::pose const & rhs):
	pos_(rhs.pos_),
	rot_(rhs.rot_)
{}
gal::math::pose::pose(gal::math::pose&& rhs):
	pos_(::std::move(rhs.pos_)),
	rot_(::std::move(rhs.rot_))
{}
gal::math::pose::pose(glm::vec3 p):
	pos_(p)
{}
gal::math::pose::pose(glm::quat q):
	pos_(0.0,0.0,0.0),
	rot_(q)
{}
gal::math::pose::pose(glm::vec3 p, glm::quat q):
	pos_(p),
	rot_(q)
{}
gal::math::pose&		gal::math::pose::operator=(gal::math::pose const & rhs) {
	pos_ = rhs.pos_;
	rot_ = rhs.rot_;
	return *this;
}
gal::math::pose		gal::math::pose::operator*(gal::math::pose const & rhs) const {
	pose ret;
	ret.pos_ = pos_ + rot_ * rhs.pos_;
	ret.rot_ = rot_ * rhs.rot_;
	return ret;
}

glm::mat4		gal::math::pose::mat4_cast() const {
	//mat4 ret(glm::mat4_cast(rot_));
	//return glm::translate(ret, vec3(pos_));

	glm::mat4 ret = glm::translate(glm::mat4(), glm::vec3(pos_)) * glm::mat4_cast(rot_);

	return ret;

}

