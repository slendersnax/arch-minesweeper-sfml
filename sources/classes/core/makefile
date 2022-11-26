.PHONY: all

all: Colours.o Entity.o helper_functions.o

Colours.o: Colours.cpp
	$(cxx) -c -Wall Colours.cpp -I $(sfml_include)

Entity.o: Entity.cpp
	$(cxx) -c -Wall Entity.cpp -I $(sfml_include)

helper_functions.o: helper_functions.cpp
	$(cxx) -c -Wall helper_functions.cpp