set(GAMES_SOURCE_DIR ${ECON-DEV_SOURCE_DIR}/Games)
set(GAME_INCLUDE ${GAMES_SOURCE_DIR}/Inc ${EPICF_PLATFORM})
list(LENGTH GAMES GAMES_LENGTH)
set(GAME_CONST_LIST_DATA ${GAMES})
list(TRANSFORM GAME_CONST_LIST_DATA PREPEND "(void*)&")
list(JOIN GAME_CONST_LIST_DATA ", " GAME_CONST_LIST_DATA)

foreach(GAME IN LISTS GAMES)
    add_subdirectory(${GAME})
    string(TOUPPER INC_${GAME} INC)
    set(INC_GAMES ${INC_GAMES} ${INC})
    set(GAME_EXTERNS "${GAME_EXTERNS}extern struct GameDescription ${GAME};\n")
endforeach()

set(GAME_CONST_LIST "static const void* gameList[GAMES_LENGTH] = { ${GAME_CONST_LIST_DATA} };")

configure_file(${GAMES_SOURCE_DIR}/Defs/game-list.h.in ${GAMES_SOURCE_DIR}/Defs/game-list.h @ONLY)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC ${INC_GAMES})
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${GAMES_SOURCE_DIR}/Defs)