all:
	gcc -Wall -O2 main.c sort.c file_io.c -o program

clean:
	rm -f program output.txt