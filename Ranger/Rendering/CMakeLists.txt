
set(RENDERING_SOURCES
        color.cpp
        rendercontext.cpp
        freetypefont.cpp
        Shaders/basic_shader.cpp
        Shaders/font_shader.cpp
        shader.cpp
        GLObjects/vao.cpp
        GLObjects/vbo.cpp
        GLObjects/ebo.cpp
        GLObjects/mesh.cpp
        )

add_library(RENDERINGLib ${RENDERING_SOURCES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# message(STATUS ${FREETYPE_INCLUDE_DIRS}) 
include_directories(
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${FREETYPE_INCLUDE_DIRS}
        )

target_link_libraries(RENDERINGLib
        ${OPENGL_LIBRARY}
        ${GLEW_LIBRARY}
        ${FREETYPE_LIBRARIES}
        RENDERING_VECTORLib
        )

