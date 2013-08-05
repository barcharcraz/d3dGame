set(util_src
	files.h
	strings.h
	math.h
	exceptions.h
	endian.h
	)
add_custom_target(utils SOURCES ${util_src})