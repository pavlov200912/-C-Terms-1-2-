obj := mergesort.c ms_cli.c
key := -Wall -Werror


all : ms_cli

ms_cli : bin $(addprefix bin/, $(obj:.c=.o))
	gcc -o $@ $(addprefix bin/, $(obj:.c=.o))  -Iinclude/ $(key)

bin/%.o : src/%.c 
	gcc -c $< -Iinclude/ -o $@

bin :
	mkdir -p bin
	
clean : 
	rm bin/*.o
	
