all:
	g++ --std=c++17 -lmpfr -lgmp -lmpc main.cpp -o thurston
clean:
	rm thurston, thurston.dbg
debug:
	g++ -g --std=c++17 -lmpfr -lgmp -lmpc main.cpp -o thurston.dbg
