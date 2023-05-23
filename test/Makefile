CXX = g++					# compiler
CXXFLAGS = -std=c++14 -g -Wall -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o game.o board.o bishop.o king.o knight.o pawn.o piece.o queen.o rook.o cpu1.o cpu2.o cpu3.o cpu4.o humanPlayer.o player.o playerFactory.o view.o graphicsView.o textView.o pos.o window.o			# object files forming executable
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
