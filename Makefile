make: main.c
	gcc -g -Wall main.c -o get_request

clean:
	rm -f get_request
