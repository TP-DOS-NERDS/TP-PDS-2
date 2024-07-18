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

${OBJ_DIR}/games/reversi.o: ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/game.h ${SRC_DIR}/game.cpp ${SRC_DIR}/games/reversi.cpp
	${CC} ${FLAGS} -o ${OBJ_DIR}/games/reversi.o -c ${SRC_DIR}/games/reversi.cpp -I ${INCLUDE_DIR}

${OBJ_DIR}/games/lig4.o: ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/game.h ${SRC_DIR}/game.cpp ${SRC_DIR}/games/lig4.cpp
	${CC} ${FLAGS} -o ${OBJ_DIR}/games/lig4.o -c ${SRC_DIR}/games/lig4.cpp -I ${INCLUDE_DIR}

${OBJ_DIR}/main.o: ${INCLUDE_DIR}/players_repository.h ${INCLUDE_DIR}/player.h ${SRC_DIR}/main.cpp
	${CC} ${FLAGS} -o ${OBJ_DIR}/main.o -c ${SRC_DIR}/main.cpp -I ${INCLUDE_DIR}

main: ${OBJ_DIR}/main.o ${OBJ_DIR}/player.o ${OBJ_DIR}/players_repository.o ${OBJ_DIR}/games/reversi.o ${OBJ_DIR}/games/lig4.o
	${CC} ${FLAGS} ${OBJ_DIR}/main.o ${OBJ_DIR}/player.o ${OBJ_DIR}/players_repository.o ${OBJ_DIR}/games/reversi.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system 

clean:
	rm -f ${OBJ_DIR}/*.o game
