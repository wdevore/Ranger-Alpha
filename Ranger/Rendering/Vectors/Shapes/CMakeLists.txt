
set(RENDERING_SHAPES_SOURCES
basic_shapes.cpp
)

include_directories(${PROJECT_SOURCE_DIR})

add_library(RENDERING_SHAPESLib ${RENDERING_SHAPES_SOURCES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    )

target_link_libraries(RENDERING_SHAPESLib
${OPENGL_LIBRARY}
)
