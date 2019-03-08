all : lab2

lab2 : bin bin/str.o bin/test_str.o bin/test.o 
	gcc -o lab2 bin/str.o bin/test_str.o bin/test.o -Iinclude/

bin :
	mkdir -p bin

bin/str.o : src/str.c 
	gcc -c src/str.c -Iinclude/ -o $@


bin/test_str.o : src/test_str.c 
	gcc -c src/test_str.c -Iinclude/ -o $@


bin/test.o : src/test.c 
	gcc -c src/test.c -Iinclude/ -o $@


clean : 
	rm bin/*.o
