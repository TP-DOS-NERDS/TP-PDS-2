CC=g++
FLAGS=-std=c++11 -Wall
OBJ=obj
SRC=src
INC=include

all: game

${OBJ}/player.o: ${SRC}/player.cpp ${INC}/player.h
	${CC} ${FLAGS} -o $@ -c $< -I$(INC)

${OBJ}/players_repository.o: ${SRC}/players_repository.cpp ${INC}/player.h
	${CC} ${FLAGS} -o $@ -c $< -I$(INC)

${OBJ}/games/minesweeper.o: ${SRC}/games/minesweeper.cpp ${INC}/player.h ${INC}/game.h
	${CC} ${FLAGS} -o $@ -c $< -I$(INC)

${OBJ}/games/reversi.o: ${SRC}/games/reversi.cpp ${INC}/player.h ${INC}/game.h
	${CC} ${FLAGS} -o $@ -c $< -I$(INC)

${OBJ}/main.o: ${SRC}/main.cpp ${INC}/players_repository.h ${INC}/player.h
	${CC} ${FLAGS} -o $@ -c $< -I$(INC)

game: ${OBJ}/main.o ${OBJ}/player.o ${OBJ}/players_repository.o ${OBJ}/games/reversi.o ${OBJ}/games/minesweeper.o
	${CC} ${FLAGS} -o $@ $^ -I$(INC)

clean:
	rm -f ${OBJ}/*.o game
