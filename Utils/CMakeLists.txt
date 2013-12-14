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
	maybe.h
    preprocess.h
	lazy_container.h
	)

add_custom_target(utils SOURCES ${util_src})
