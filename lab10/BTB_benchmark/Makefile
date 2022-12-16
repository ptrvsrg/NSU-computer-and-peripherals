all: run

run: BTB_benchmark.c branches
	gcc BTB_benchmark.c branches.h -o bin/BTB_benchmark -I../papi-install/include -L../papi-install/lib -Wl,-rpath=../papi-install/lib -lpapi

branches: create_branches.c
	gcc create_branches.c -o bin/create_branches
	bin/create_branches ${count_branches} ${offset}