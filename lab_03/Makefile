all : pose_db

pose_db : bin bin/main.o bin/clist.o  
	gcc -o  pose_db bin/main.o bin/clist.o -Iinclude/ -Wall -Werror

bin :
	mkdir -p bin

bin/main.o : src/main.c 
	gcc -c src/main.c -Iinclude/ -o $@ -Wall -Werror


bin/clist.o : src/clist.c 
	gcc -c src/clist.c -Iinclude/ -o $@ -Wall -Werror

clean : 
	rm bin/*.o
