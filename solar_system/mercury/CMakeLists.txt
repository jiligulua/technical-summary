file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cc include/*.h)
add_library(mercury STATIC ${src})
target_include_directories(mercury PUBLIC include)
