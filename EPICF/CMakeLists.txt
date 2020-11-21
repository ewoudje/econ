include_directories(Inc ${EPICF_PLATFORM})

file(GLOB_RECURSE SOURCES "Src/*.*")

add_library(EPICF ${SOURCES})