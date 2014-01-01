include(ExternalProject)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
macro(install_eigen)
	ExternalProject_Add(Eigen3
						URL https://bitbucket.org/eigen/eigen/get/default.tar.gz
						CMAKE_ARGS -DEIGEN_INCLUDE_INSTALL_DIR:path=<INSTALL_DIR>
										 -DCMAKE_INSTALL_PREFIX:path=<INSTALL_DIR>
										 -DEIGEN_LEAVE_TEST_IN_ALL_TARGET:BOOL=OFF
										 -DCMAKE_Fortran_COMPILER=CMAKE_Fortran_COMPILER-NOTFOUND
						)
	ExternalProject_Get_Property(Eigen3 install_dir)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${install_dir})
	set_property(TARGET Eigen3 PROPERTY FOLDER "External")
endmacro()
macro(install_glfw3)
	ExternalProject_Add(glfw3
						GIT_REPOSITORY https://github.com/barcharcraz/glfw.git
						CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
								   -DGLFW_USE_DWM_SWAP_INTERVAL=ON
								   -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF
								   -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
						)
    ExternalProject_Get_Property(glfw3 install_dir)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${install_dir})
	set_property(TARGET glfw3 PROPERTY FOLDER "External")
endmacro()
macro(install_gtest)
	if(MSVC)
		set(platform_gtest_args -DCMAKE_DEBUG_POSTFIX:STRING=d)
	endif()
	ExternalProject_Add(
    gtest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=Libs
			   -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Libs
			   -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Libs
               -Dgtest_disable_pthreads:BOOL=ON
			   ${platform_gtest_args}
    # Disable install step
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory 
                        <SOURCE_DIR>/include <INSTALL_DIR>/include
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        <BINARY_DIR>/Libs <INSTALL_DIR>/lib
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

	ExternalProject_Get_Property(gtest source_dir)
	ExternalProject_Get_Property(gtest install_dir)
	set(GTEST_ROOT ${install_dir} CACHE PATH "gtest install dir")
	set_property(TARGET gtest PROPERTY FOLDER "External")
endmacro()
