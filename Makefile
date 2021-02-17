.DEFAULT_GOAL := build

2DLIBS = -lsimple2d -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -pthread -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf
build: 
	@echo "Creating build directory"
	@mkdir build/
	@echo "Formatting CPP files with clang-format"
	@clang-format -i src/*.cpp
	@echo "Compiling main.cpp"
	@g++ src/main.cpp ${2DLIBS} -o build/game
	@echo "Enabling execute permission"
	@chmod +x build/game
	@echo "Copying media files"
	@cp -r media build

clean: 
	@echo "Deleting build directory..."
	@rm -rf build/

remake: clean build
