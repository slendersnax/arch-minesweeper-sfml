export cxx = g++
export sfml_include = /usr/include/SFML
export sfml_lib = /usr/lib
export included_libs = -lsfml-graphics -lsfml-window -lsfml-system
mine_files = main.o classes/Game.o classes/core/Entity.o classes/core/Colours.o classes/core/helper_functions.o

.PHONY: classes clean

minesweeper: classes main.o
	mkdir -p ../bin
	$(cxx) $(mine_files) -o ../bin/minesweeper -L $(sfml_lib) $(included_libs)

main.o: classes main.cpp
	$(cxx) -c -Wall main.cpp -I $(sfml_include)

classes:
	$(MAKE) -C classes

clean:
	rm -r *.o
	rm -r classes/*.o
	rm -r classes/core/*.o

run:
	../bin/minesweeper