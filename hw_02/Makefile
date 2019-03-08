obj := main.cpp Board.cpp  BoardView.cpp
obj1 := BoardTest.cpp test.cpp Board.cpp Test.cpp
key := -std=c++03 -Wall -Werror


all : main

main : bin $(addprefix bin/, $(obj:.cpp=.o))
	g++ -o $@ $(addprefix bin/, $(obj:.cpp=.o))  -Iinclude/ $(key) 

bin/%.o : src/%.cpp 
	g++ -c $< -Iinclude/ -o $@ $(key) 
	
bin/%.o : test/%.cpp
	g++ -c $< -Iinclude/ -o $@ $(key) 
	
bin :
	mkdir -p bin
	
clean : 
	rm -rf bin main board_test
	
board_test: bin $(addprefix bin/, $(obj1:.cpp=.o))
	g++ -o $@ $(addprefix bin/, $(obj1:.cpp=.o))  -Iinclude/ $(key) 
	
