#project(GLFWBeta)

set(GLFW_SOURCES
        window.cpp
        time.cpp
        )

include_directories(${PROJECT_SOURCE_DIR})

add_library(GLFWLib ${GLFW_SOURCES})

find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

include_directories(
        ${GLFW_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${FREETYPE_INCLUDE_DIRS}
)

target_link_libraries(GLFWLib
        ${GLFW_LIBRARY}
        ${GLEW_LIBRARY}
        IOLib
        RENDERINGLib
        )
