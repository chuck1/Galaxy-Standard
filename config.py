"""
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(galaxy_std)
INCLUDE(../../../../config.cmake)
INCLUDE(cmh_build_config)

SET(SHARED True)

INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
	REQUIRED)

#INCLUDE_DIRECTORIES("/usr/include/python2.7")

SET(libs
	${Boost_LIBRARIES}
	pthread
	)

INCLUDE(cmh_library)

ADD_SUBDIRECTORY(test)
"""

l = Static("galaxy_std")

l.libs.append("dl")

l.tests.append("galaxy_std_test_registry");
l.tests.append("galaxy_std_test_map");
l.tests.append("galaxy_std_test_serial");
l.tests.append("galaxy_std_test_weak_ptr");
l.tests.append("galaxy_std_test_tuple");

l.make()


include("test")


