all : RoundRobin.o
	 gcc -g -o RoundRobin RoundRobin.c
RoundRobin.o : RoundRobin.c
	 gcc -g -c RoundRobin.c	
clean:
	 rm -f RoundRobin RoundRobin.o

