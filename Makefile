.DEFAULT_GOAL := usage

2DLIBS = 
COMPILER = g++
FORMATTER = clang-format -i
BUILDDIR = build

usage:
	@echo "USAGE:"
	@echo "make build to build"
	@echo "make pretty to make the code pretty"
	@echo "make clean to make it clean"
	@echo "make remake to remake"

pretty:
	@echo "Linting CPP files"
	@${FORMATTER} src/*.cpp

build: pretty
	@echo "Creating build directory"
	@mkdir ${BUILDDIR}/
	@echo "Compiling main.cpp"
	@${COMPILER} src/main.cpp ${2DLIBS} -o ${BUILDDIR}/game
	@echo "Enabling execute permission"
	@chmod +x ${BUILDDIR}/game
	@echo "Copying media files"
	@cp -r media ${BUILDDIR}

clean: 
	@echo "Deleting build directory..."
	@rm -rf ${BUILDDIR}/

remake: clean build
