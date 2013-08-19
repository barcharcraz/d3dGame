set(libcairo_files
  Renderer.h,
  Renderer.cpp
  )
add_library(CairoRenderer STATIC ${libcairo_files})
target_link_libraries(Components2D)