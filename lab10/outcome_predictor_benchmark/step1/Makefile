all: make_bin main.c
	gcc main.c -o bin/main

make_bin:
	[ ! -d "bin" ] && mkdir bin &> /dev/null

clean:
	rm -rf bin