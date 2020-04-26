
set(CORE_TIMING_SOURCES
scheduler.cpp
timer.cpp
timing_target.cpp
update_target.cpp
)

include_directories(${PROJECT_SOURCE_DIR})

add_library(CORE_TIMINGLib
${CORE_TIMING_SOURCES}
)