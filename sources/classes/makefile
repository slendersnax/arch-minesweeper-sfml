.PHONY: core all

all: Game.o core

Game.o: core Game.cpp
	$(cxx) -o Game.o -c -Wall Game.cpp -I $(sfml_include) -I core

core:
	$(MAKE) -C core