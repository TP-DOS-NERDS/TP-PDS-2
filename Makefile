CC=g++
FLAGS=-std=c++11 -Wall
OBJ_DIR=obj
SRC_DIR=src
INCLUDE_DIR=include

all: main

${OBJ_DIR}/player.o: ${INCLUDE_DIR}/player.h ${SRC_DIR}/player.cpp
	${CC} ${FLAGS} -c ${SRC_DIR}/player.cpp -I ${INCLUDE_DIR} -o ${OBJ_DIR}/player.o

${OBJ_DIR}/players_repository.o: ${SRC_DIR}/players_repository.cpp ${INCLUDE_DIR}/player.h
	${CC} ${FLAGS} -o ${OBJ_DIR}/players_repository.o -c ${SRC_DIR}/players_repository.cpp -I ${INCLUDE_DIR}

${OBJ_DIR}/games/snake.o: ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/game.h ${SRC_DIR}/game.cpp ${SRC_DIR}/games/snake.cpp
	${CC} ${FLAGS} -o ${OBJ_DIR}/games/snake.o -c ${SRC_DIR}/games/snake.cpp -I ${INCLUDE_DIR}

${OBJ_DIR}/main.o: ${INCLUDE_DIR}/players_repository.h ${INCLUDE_DIR}/player.h ${SRC_DIR}/main.cpp
	${CC} ${FLAGS} -o ${OBJ_DIR}/main.o -c ${SRC_DIR}/main.cpp -I ${INCLUDE_DIR}

main: ${OBJ_DIR}/main.o ${OBJ_DIR}/player.o ${OBJ_DIR}/players_repository.o ${OBJ_DIR}/games/snake.o
	${CC} ${FLAGS} ${OBJ_DIR}/main.o ${OBJ_DIR}/player.o ${OBJ_DIR}/players_repository.o ${OBJ_DIR}/games/snake.o -o game

clean:
	rm -f ${OBJ_DIR}/*.o game