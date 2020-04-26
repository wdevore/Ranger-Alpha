
set(CORE_SOURCES transform.cpp transform.h)

add_library(CORELib ${CORE_SOURCES})

find_package(GLM REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})

