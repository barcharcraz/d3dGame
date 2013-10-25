include(ExternalProject)
macro(install_eigen)
    ExternalProject_Add(Eigen3
                        HG_REPOSITORY https://bitbucket.org/eigen/eigen/
                        HG_TAG 3.2.0
                        BUILD ""
endmacro()
