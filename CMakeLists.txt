set(ENGINE_SOURCES
        ranger.cpp
        engine.cpp
        )

include_directories(${PROJECT_SOURCE_DIR})

add_library(ENGINELib STATIC ${ENGINE_SOURCES})

find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

include_directories(
        ${GLFW_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${FREETYPE_INCLUDE_DIRS}
)

target_link_libraries(ENGINELib
        ${GLFW_LIBRARY}
        ${GLEW_LIBRARY}
        IOLib
        GRAPHICSLib
        COMPONENTSLib
        )
