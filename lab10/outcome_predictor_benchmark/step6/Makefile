all: make_bin main.c
	gcc main.c -o bin/main -I../../papi-install/include -L../../papi-install/lib -Wl,-rpath=../../papi-install/lib -lpapi

make_bin:
	[ ! -d "bin" ] && mkdir bin &> /dev/null

clean:
	rm -rf bin