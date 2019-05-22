all:
	g++ --std=c++17 -lmpfr -lboost_program_options -lgmp -lmpc main.cpp -o thurston
clean:
	rm -f thurston thurston.dbg # 2> /dev/null
debug:
	g++ -g --std=c++17 -lmpfr -lgmp -lboost_program_options -lmpc main.cpp -o thurston.dbg
