FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -g -I. -ICode -IGHOST -I/opt/homebrew/opt/sfml@2/include
LIB = -L/opt/homebrew/opt/sfml@2/lib -lsfml-graphics -lsfml-system -lsfml-window

pacman: Code/main.cc game.o entity.o pacman.o ghost_wrapper.o grid.o ghost.o
	g++ $(FLAGS) -o pacman Code/main.cc game.o entity.o pacman.o ghost_wrapper.o grid.o ghost.o $(LIB)

ghost.o: Code/ghost.cpp Code/ghost.h
	g++ -o ghost.o $(FLAGS) -c Code/ghost.cpp

%.o: Code/%.cc Code/%.h
	g++ $(FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f *.o ./pacman
