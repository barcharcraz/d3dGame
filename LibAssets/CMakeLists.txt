set(libassets_files
  GeometryFile.h
  ObjFile.cpp
  ObjFile.h
  stdafx.cpp
  stdafx.h
  )
add_library(AssetLoader STATIC ${libassets_files})