CC=g++
FLAGS=-std=c++11 -Wall -g
OBJ_DIR=obj
SRC_DIR=src
INCLUDE_DIR=include
TESTS_DIR=tests
TESTS=u

all: main

${OBJ_DIR}/game_ids.o: ${SRC_DIR}/game_ids.cpp ${INCLUDE_DIR}/game_ids.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/player.o: ${SRC_DIR}/player.cpp ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/game_ids.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/player_repository.o: ${SRC_DIR}/player_repository.cpp ${INCLUDE_DIR}/player_repository.h  ${INCLUDE_DIR}/player.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/lig4.o: ${SRC_DIR}/games/lig4.cpp ${INCLUDE_DIR}/games/lig4.h ${INCLUDE_DIR}/game.h ${INCLUDE_DIR}/IOHandler.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/reversi.o: ${SRC_DIR}/games/reversi.cpp ${INCLUDE_DIR}/games/reversi.h ${INCLUDE_DIR}/game.h ${INCLUDE_DIR}/IOHandler.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}


#${OBJ_DIR}/snake.o: ${SRC_DIR}/games/snake.cpp ${INCLUDE_DIR}/games/snake.h ${INCLUDE_DIR}/game.h ${INCLUDE_DIR}/IOHandler.h ${INCLUDE_DIR}/terminal_handler.h
#	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/game_center.o: ${SRC_DIR}/game_center.cpp ${INCLUDE_DIR}/games/lig4.h ${INCLUDE_DIR}/game_center.h ${INCLUDE_DIR}/game.h  ${INCLUDE_DIR}/games/reversi.h ${INCLUDE_DIR}/player_repository.h ${INCLUDE_DIR}/player.h ${INCLUDE_DIR}/IOHandler.h  ${INCLUDE_DIR}/games/snake.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}


#${OBJ_DIR}/terminal_handler.o: ${SRC_DIR}/terminal_handler.cpp ${INCLUDE_DIR}/terminal_handler.h
#	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}


ifdef TESTS
${OBJ_DIR}/player_tests.o: ${TESTS_DIR}/player_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/player_repository_tests.o: ${TESTS_DIR}/player_repository_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/game_ids_tests.o: ${TESTS_DIR}/game_ids_tests.cpp
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/IOHandler_tests.o: ${TESTS_DIR}/IOHandler_tests.cpp ${INCLUDE_DIR}/IOHandler.h ${TESTS_DIR}/CinRedirector.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/lig4_tests.o: ${TESTS_DIR}/lig4_tests.cpp ${INCLUDE_DIR}/IOHandler.h ${TESTS_DIR}/CinRedirector.h ${TESTS_DIR}/CoutRedirector.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

${OBJ_DIR}/game_center_tests.o : ${TESTS_DIR}/game_center_tests.cpp ${INCLUDE_DIR}/game_center.h ${INCLUDE_DIR}/forbidden_action_exception.h ${TESTS_DIR}/CinRedirector.h ${TESTS_DIR}/CoutRedirector.h
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

main: ${OBJ_DIR}/lig4_tests.o ${OBJ_DIR}/IOHandler_tests.o ${OBJ_DIR}/player_tests.o ${OBJ_DIR}/game_center_tests.o ${OBJ_DIR}/game_ids_tests.o ${OBJ_DIR}/player_repository_tests.o ${OBJ_DIR}/game_center.o ${OBJ_DIR}/player_repository.o ${OBJ_DIR}/player.o ${OBJ_DIR}/game_ids.o ${OBJ_DIR}/lig4.o #${OBJ_DIR}/snake.o ${OBJ_DIR}/terminal_handler.o
	${CC} ${FLAGS} -o $@ $^ -I ${INCLUDE_DIR}

else
${OBJ_DIR}/main.o: ${SRC_DIR}/main.cpp ${INCLUDE_DIR}/game_center.h 
	${CC} ${FLAGS} -o $@ -c $< -I ${INCLUDE_DIR}

main:	${OBJ_DIR}/main.o ${OBJ_DIR}/reversi.o ${OBJ_DIR}/game_center.o ${OBJ_DIR}/lig4.o ${OBJ_DIR}/player_repository.o ${OBJ_DIR}/player.o ${OBJ_DIR}/game_ids.o #${OBJ_DIR}/terminal_handler.o# ${OBJ_DIR}/snake.o
	${CC} ${FLAGS} -o $@ $^ -I ${INCLUDE_DIR}

endif

clean:
	rm obj/main.o
