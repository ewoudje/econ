file(GLOB_RECURSE SOURCES "Src/*.*")

add_library(TestGame ${SOURCES})
target_include_directories(TestGame PUBLIC Inc ${GAME_INCLUDE})