file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cc include/*.h)
add_library(asteroid STATIC ${src})
target_include_directories(asteroid PUBLIC include)
