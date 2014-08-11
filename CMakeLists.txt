CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(galaxy_std)

SET(galaxy_std_STATIC TRUE)
SET(galaxy_std_SHARED TRUE)

FIND_PACKAGE(CMakeHelper)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions( -DBOOST_ALL_DYN_LINK )

FIND_PACKAGE(Boost 1.55 COMPONENTS
	system
	thread
	REQUIRED)

INCLUDE_DIRECTORIES("/usr/include/python2.7")


SET(libs
	${Boost_LIBRARIES}
	pthread
	rt
	dl
	)

cmh_library()

#ADD_SUBDIRECTORY(test)

