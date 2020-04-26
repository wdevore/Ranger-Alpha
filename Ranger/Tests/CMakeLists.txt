
set(TESTS_SOURCES
        Test_Shell.cpp
        Test_Engine.cpp
        )

include_directories(${PROJECT_SOURCE_DIR})

add_library(TESTLib ${TESTS_SOURCES})

find_package(GLM REQUIRED)

#message(STATUS ${GLM_INCLUDE_DIRS})
include_directories(
        ${GLM_INCLUDE_DIRS}
)

target_link_libraries(TESTLib
        ENGINELib
        GLFWLib
        )

