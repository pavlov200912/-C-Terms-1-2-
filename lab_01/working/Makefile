obj := main.c util.c io.c algorithm.c

all : lab1

lab1 : $(addprefix bin/, $(obj:.c=.o))
	gcc -o $@ $(addprefix bin/, $(obj:.c=.o))  -Iinclude/

bin/%.o : src/%.c 
	gcc -c $< -Iinclude/ -o $@

clean : 
	rm bin/*.o
