arg = --std=c++17 -lmpfr -lboost_program_options -lmpc

all:
	g++ $(arg)  main.cpp -o thurston
clean:
	rm -f thurston thurston.dbg # 2> /dev/null
debug:
	g++ -g $(arg) main.cpp -o thurston.dbg
