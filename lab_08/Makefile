obj := main.cpp matrix.cpp
key := -std=c++98 -Wall -Werror


all : main

main : bin $(addprefix bin/, $(obj:.cpp=.o))
	g++ -o $@ $(addprefix bin/, $(obj:.cpp=.o))  -Iinclude/ $(key)  -lexpat 

bin/%.o : src/%.cpp 
	g++ -c $< -Iinclude/ -o $@ 

bin :
	mkdir -p bin
	
clean : 
	rm bin/*.o
	
