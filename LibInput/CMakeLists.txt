set(input_files 
	KeyCombination.cpp
	Input.cpp
	Keys.h
	KeyCombination.h
	Input.h
	Axis.h
	Axis.cpp
	DeviceTypes.h
	stdafx.h
	stdafx.cpp
	)
add_library(Input STATIC ${input_files})