obj := main.cpp huffman.cpp
obj1 := huffman.cpp huffman_test.cpp test.cpp autotest.cpp
key := -std=c++17 -Wall -Werror


all : huffman

huffman : bin $(addprefix bin/, $(obj:.cpp=.o))
	g++ -o $@ $(addprefix bin/, $(obj:.cpp=.o))  -Iinclude/ $(key)

bin/%.o : src/%.cpp
	g++ -c $< -Iinclude/ -o $@ $(key)

bin/%.o : test/%.cpp
	g++ -c $< -Iinclude/ -Itest/ -o $@ $(key)

bin :
	mkdir -p bin

clean :
	rm -rf bin huffman hf_test test.bin test.txt text.txt

hf_test: bin $(addprefix bin/, $(obj1:.cpp=.o))
	g++ -o $@ $(addprefix bin/, $(obj1:.cpp=.o))  -Iinclude/ -Itest/  $(key)
