obj := main.c bmp.c message.c
key := -Wall -Werror -std=c99


all : main

main : bin $(addprefix bin/, $(obj:.c=.o))
	gcc -o $@ $(addprefix bin/, $(obj:.c=.o))  -Iinclude/ $(key)   

bin/%.o : src/%.c 
	gcc -c $< -Iinclude/ -o $@ 

bin :
	mkdir -p bin
	
clean : 
	rm bin/*.o
	rm main
	
