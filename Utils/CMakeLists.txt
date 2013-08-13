set(util_src
	files.h
	strings.h
	math.h
	exceptions.h
	endian.h
	sets.h
    make_unique.h
	identifier.h
	)
add_custom_target(utils SOURCES ${util_src})