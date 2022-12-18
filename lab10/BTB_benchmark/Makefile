all: run

run: main.c branches
	gcc main.c branches.h -o bin/main -I../papi-install/include -L../papi-install/lib -Wl,-rpath=../papi-install/lib -lpapi

branches: create_branches.c make_bin
	gcc create_branches.c -o bin/create_branches -lm
	bin/create_branches ${branch_count}

make_bin:
	[ ! -d "bin" ] && mkdir bin &> /dev/null

clean:
	rm -rf bin
	rm -f branches.h