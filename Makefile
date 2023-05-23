CXX = g++					# compiler
CXXFLAGS = -std=c++14 -g -Wall -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o game/game.o board/board.o board/bishop.o board/king.o board/knight.o board/pawn.o board/piece.o board/queen.o board/rook.o player/cpu1.o player/cpu2.o player/cpu3.o player/cpu4.o player/humanPlayer.o player/player.o player/playerFactory.o view/view.o view/graphicsView.o view/textView.o pos.o view/window.o			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = chess					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS}  $^ -o $@ -lX11		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
