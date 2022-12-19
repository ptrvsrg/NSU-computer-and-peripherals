all: run

run: make_bin create_code
	gcc main.c -o bin/main

create_code: create_code.c
	rm -f main.c &> /dev/null
	gcc create_code.c -o bin/create_code
	bin/create_code ${dummy_branch_count}

make_bin:
	[ ! -d "bin" ] && mkdir bin &> /dev/null

clean:
	rm -rf bin
