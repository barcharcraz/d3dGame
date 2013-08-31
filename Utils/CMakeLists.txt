set(util_src
	files.h
	strings.h
	math.h
	exceptions.h
	endian.h
        sets.h
        make_unique.h
        container.h
	identifier.h
	functions.h
	event.h
	)
find_package(Boost)
if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})
set(BOOST_USE_FLATMAPS ON CACHE BOOL "use boost::flat_map and boost::flat_set as a replacement for the std versions")
else(BOOST_FOUND)
set(Boost_USE_FLATMAPS OFF CACHE BOOL "use boost::flat_map and boost::flat_set as a replacement for the std versions")
endif(Boost_FOUND)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
add_custom_target(utils SOURCES ${util_src})
