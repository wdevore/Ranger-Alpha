
set(IO_SOURCES
        base64.cpp
        configuration.cpp
        json11.cpp
        )

include_directories(${PROJECT_SOURCE_DIR})

add_library(IOLib ${IO_SOURCES})