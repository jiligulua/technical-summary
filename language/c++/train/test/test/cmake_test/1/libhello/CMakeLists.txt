set(LIB_SRC hello.c)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if(BUILD_SHARED)	
	add_library(libhello SHARED ${LIB_SRC})
else()
	add_library(libhello STATIC ${LIB_SRC})
endif()
