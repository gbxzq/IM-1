.DEFAULT_GOAL := build

build_linux:
	@mkdir bin; cd bin;gcc ../src/main.c ../lib/random.c

build_win:
	@cd bin; x86_64-w64-mingw32-gcc -o main64.exe ../src/main.c ../lib/random.c 

build:
	make build_linux
	make build_win