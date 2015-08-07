#include <gal/_release.hpp>

typedef gal::_release THIS;

THIS::~_release()
{
}
void		THIS::release()
{
        sig_release_(shared_from_this());
}


