.PHONY: all

all:
	mkdir build || true
	gcc main.c -o ./build/mwav
	gcc reverse.c -o ./build/mwavr
