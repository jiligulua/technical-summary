file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cc include/*.h)
add_executable(main ${src})

target_include_directories(main PUBLIC include)

find_package(TBB CONFIG REQUIRED COMPONENTS tbb)
target_link_libraries(main PUBLIC TBB::tbb)

find_package(Boost 1.81.0 CONFIG REQUIRED COMPONENTS container)
target_link_libraries(main PUBLIC Boost::container)

target_link_libraries(main PUBLIC mercury)
target_link_libraries(main PUBLIC asteroid)
