arg = --std=c++17 -lmpfr -lboost_program_options -lmpc

all:
	g++ $(arg)  src/main.cpp -o bin/thurston
clean:
	rm -f bin/thurston bin/thurston.dbg
debug:
	g++ -g $(arg) src/main.cpp -o bin/thurston.dbg
