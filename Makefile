all:
	g++ --std=c++17 main.cpp -o thurston
clean:
	rm thurston, thurston.dbg
debug:
	g++ -g --std=++17 main.cpp -o thurston.dbg
