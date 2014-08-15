CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(galaxy_std)

FIND_PACKAGE(CMakeHelper)

cmh_boost_shared()
FIND_PACKAGE(Boost 1.55 COMPONENTS
	system
	thread
	REQUIRED)

#INCLUDE_DIRECTORIES("/usr/include/python2.7")

SET(libs
	${Boost_LIBRARIES}
	pthread
	rt
	dl
	)

cmh_static_library()

#ADD_SUBDIRECTORY(test)

PROJECT(galaxy_std_shared)

FIND_PACKAGE(CMakeHelper)

cmh_boost_shared()
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

cmh_shared_library()

