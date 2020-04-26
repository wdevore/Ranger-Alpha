
set(GRAPHICS_SOURCES
        viewport.cpp
        view.cpp
        camera.cpp)

include_directories(${PROJECT_SOURCE_DIR})

add_library(GRAPHICSLib ${GRAPHICS_SOURCES})

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

include_directories(
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
)

target_link_libraries(GRAPHICSLib
        ${GLEW_LIBRARY}
        )
