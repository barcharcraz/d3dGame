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

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
add_custom_target(utils SOURCES ${util_src})
