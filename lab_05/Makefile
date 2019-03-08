obj := clist.c main.c position.c
key := -Wall -Werror


all : main

main : bin $(addprefix bin/, $(obj:.c=.o))
	gcc -o $@ $(addprefix bin/, $(obj:.c=.o))  -Iinclude/ $(key)

bin/%.o : src/%.c 
	gcc -c $< -Iinclude/ -o $@

bin :
	mkdir -p bin
	
clean : 
	rm bin/*.o
	
