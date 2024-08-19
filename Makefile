CC=g++
FLAGS=-std=c++11 -Wall
OBJ_DIR=obj
SRC_DIR=src
INCLUDE_DIR=include
TESTS=true

all: main

${OBJ_DIR}/game_ids.o: ${SRC_DIR}/game_ids.cpp ${INCLUDE_DIR}/game_ids.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/player.o: ${SRC_DIR}/player.cpp ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/game_ids.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/player_repository.o: ${SRC_DIR}/player_repository.cpp ${INCLUDE_DIR}/player_repository.h  ${INCLUDE_DIR}/player.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/game_center.o: ${SRC_DIR}/game_center.cpp ${INCLUDE_DIR}/game_center.h ${INCLUDE_DIR}/player_repository.h ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/IOHandler.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

ifdef TESTS
${OBJ_DIR}/player_tests.o: tests/player_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}
${OBJ_DIR}/player_repository_tests.o: tests/player_repository_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}
${OBJ_DIR}/game_ids_tests.o: tests/game_ids_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}
${OBJ_DIR}/IOHandler_tests.o: tests/IOHandler_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}
main: ${OBJ_DIR}/IOHandler_tests.o ${OBJ_DIR}/player_tests.o ${OBJ_DIR}/game_ids_tests.o ${OBJ_DIR}/player_repository_tests.o ${OBJ_DIR}/game_center.o ${OBJ_DIR}/player_repository.o ${OBJ_DIR}/player.o ${OBJ_DIR}/game_ids.o 
	${CC} ${FLAGS} -o $@ $^ -I ${INCLUDE_DIR}

else
${OBJ_DIR}/main.o: ${SRC_DIR}/main.cpp ${INCLUDE_DIR}/game_center.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}
main: ${OBJ_DIR}/main.o ${OBJ_DIR}/game_center.o ${OBJ_DIR}/player_repository.o ${OBJ_DIR}/player.o ${OBJ_DIR}/game_ids.o 
	${CC} ${FLAGS} -o $@ $^ -I ${INCLUDE_DIR}
endif

clean:
	rm obj/main.o
