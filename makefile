all: client

client: client.o bigNumber.o manageMemory.o bigNumberUtils.o
	gcc client.o bigNumber.o manageMemory.o bigNumberUtils.o -lm -o client

client.o: client.c bigNumber.h manageMemory.h bigNumberUtils.h
	gcc -std=c99 -g -Wall -Wextra -Wvla -g -c client.c -lm

bigNumber.o: bigNumber.c bigNumber.h manageMemory.h
	gcc -std=c99 -g -Wall -Wextra -Wvla -g -c bigNumber.c -lm

manageMemory.o: manageMemory.c manageMemory.h bigNumber.h
	gcc -std=c99 -g -Wall -Wextra -Wvla -g -c manageMemory.c -lm

bigNumberUtils.o: bigNumberUtils.c bigNumberUtils.h bigNumber.h
	gcc -std=c99 -g -Wall -Wextra -Wvla -g -c bigNumberUtils.c -lm