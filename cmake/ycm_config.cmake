macro(activate_ycm)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py.in ${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endmacro(activate_ycm)
