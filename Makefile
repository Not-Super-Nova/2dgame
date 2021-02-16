.DEFAULT_GOAL := build

2DLIBS = -lsimple2d -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -pthread -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf
build: 
	mkdir build/
	g++ src/main.cpp ${2DLIBS} -o build/game
	chmod +x build/game

clean: 
	rm -rf build/
