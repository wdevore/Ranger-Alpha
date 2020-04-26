
set(NODES_SOURCES
basenode.cpp
)

add_library(NODESLib
${NODES_SOURCES}
)

# Now define the link order dependencies.
# The dependencies "flow" downward, for example, Nodes library depends on core_timing
# library so the first entry is NODESLib and the second is CORE_TIMINGLib
target_link_libraries(NODESLib
CORE_TIMINGLib
)
