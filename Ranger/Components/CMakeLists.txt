
set(COMPONENTS_SOURCES 
stage.cpp
scene_manager.cpp
transition_scene.cpp
)

include_directories(${PROJECT_SOURCE_DIR})

add_library(COMPONENTSLib ${COMPONENTS_SOURCES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    )

target_link_libraries(COMPONENTSLib
    RENDERINGLib
    NODESLib
    RENDERING_SHAPESLib
    ${GLEW_LIBRARY}
    ${OPENGL_LIBRARY}
    ${FREETYPE_LIBRARIES}
    )
