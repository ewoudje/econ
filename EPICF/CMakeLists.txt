set(EPICF_SOURCE_DIR ${ECON-DEV_SOURCE_DIR}/EPICF)
set(EPICF_INC ${EPICF_SOURCE_DIR}/Inc)

file(GLOB_RECURSE SOURCES "Src/*.*")

add_library(EPICF ${SOURCES})
target_include_directories(EPICF PUBLIC ${EPICF_INC} ${EPICF_PLATFORM})
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${EPICF_SOURCE_DIR}/Platform)