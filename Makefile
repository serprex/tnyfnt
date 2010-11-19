t:tf5x5 tf3x5 test
ifneq ($(GLX),)
CFLAGS=-DGLX
else
CFLAGS=-DSDL `sdl-config --cflags` `sdl-config --libs` -lSDL_net
endif
CC=gcc -std=gnu99 -Os -march=native -s -ffast-math -ftree-vectorize -o
tf5x5:tf5x5.c
	${CC} tf5x5.o -c tf5x5.c ${CFLAGS}
tf3x5:tf3x5.c
	${CC} tf3x5.o -c tf3x5.c ${CFLAGS}
test:tf3x5 tf5x5 test.c
	${CC} test5x5 tf5x5.o test.c ${CFLAGS} -lGL
	${CC} test3x5 tf3x5.o test.c ${CFLAGS} -lGL