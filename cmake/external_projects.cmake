include(ExternalProject)
macro(install_eigen)
    ExternalProject_Add(Eigen3
                        HG_REPOSITORY https://bitbucket.org/eigen/eigen/
                        HG_TAG default
                        CMAKE_CACHE_ARGS -DEIGEN_INCLUDE_INSTALL_DIR:path=<INSTALL_DIR>
                                         -DCMAKE_INSTALL_PREFIX:path=<INSTALL_DIR>
                        )
    ExternalProject_Get_Property(Eigen3 install_dir)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${install_dir})
endmacro()
