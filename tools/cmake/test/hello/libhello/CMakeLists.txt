#set(LIB_SRC hello.c)

file(GLOB LIB_SRC CONFIGURE_DEPENDS *.c *cpp *.h)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if(BUILD_SHARED)
  add_library(libhello SHARED ${LIB_SRC})
else()
#add_library(libhello STATIC ${LIB_SRC})
  add_library(libhello OBJECT ${LIB_SRC})
endif()
