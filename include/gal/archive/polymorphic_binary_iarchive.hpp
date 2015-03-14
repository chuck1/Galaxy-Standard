#ifndef NEB_FND_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP
#define NEB_FND_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP

//MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#include <gal/archive/archive.hpp>

namespace gal { namespace archive {
	class polymorphic_binary_iarchive:
		public gal::archive::archive,
		public boost::archive::detail::polymorphic_iarchive_route<boost::archive::naked_binary_iarchive>
	{
	public:
		polymorphic_binary_iarchive(std::istream & is, unsigned int flags = 0):
			boost::archive::detail::polymorphic_iarchive_route<boost::archive::naked_binary_iarchive>(is, flags)
		{
		}
		~polymorphic_binary_iarchive()
		{
		}
	};
}}

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
		gal::archive::polymorphic_binary_iarchive
		)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP











