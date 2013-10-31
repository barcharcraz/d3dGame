include(ExternalProject)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
macro(install_eigen)
	ExternalProject_Add(Eigen3
						HG_REPOSITORY https://bitbucket.org/eigen/eigen/
						HG_TAG default
						CMAKE_CACHE_ARGS -DEIGEN_INCLUDE_INSTALL_DIR:path=<INSTALL_DIR>
										 -DCMAKE_INSTALL_PREFIX:path=<INSTALL_DIR>
						)
	ExternalProject_Get_Property(Eigen3 install_dir)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${install_dir})
	set_property(TARGET Eigen3 PROPERTY FOLDER "External")
endmacro()
macro(install_glfw3)
	ExternalProject_Add(glfw3
						GIT_REPOSITORY https://github.com/glfw/glfw.git
						GIT_TAG master
                        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
						)
    ExternalProject_Get_Property(glfw3 install_dir)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${install_dir})
	set_property(TARGET glfw3 PROPERTY FOLDER "External")
endmacro()
macro(install_gtest)
	ExternalProject_Add(
    gtest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=Libs
               -Dgtest_disable_pthreads:BOOL=ON
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
