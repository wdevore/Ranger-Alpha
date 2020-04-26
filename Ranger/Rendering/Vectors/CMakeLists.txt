
set(RENDERING_VECTORS_SOURCES
vector_atlas.cpp
vector_shape.cpp
vector_uniform_atlas.cpp
uniform_atlas.cpp
atlas.cpp
vector_object.cpp
)

include_directories(${PROJECT_SOURCE_DIR})

add_library(RENDERING_VECTORLib ${RENDERING_VECTORS_SOURCES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR})

target_link_libraries(RENDERING_VECTORLib
${OPENGL_LIBRARY}
RENDERINGLib
)
