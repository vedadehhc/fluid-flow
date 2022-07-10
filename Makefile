#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard *.cpp)
SOURCES = $(wildcard *.h) $(wildcard *.cpp)

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I.\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L.\lib

#BIN_PATH specifies the path to binaries to copy into build folder
BIN_PATH = bin

#RESOURCE_PATH specifies the path to application resources (images, fonts, etc.)
RESOURCE_PATH = resources

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
# -static-libgcc -static-libstdc++ compiles statically
RELEASE_COMPILER_FLAGS = -w -Wl,-subsystem,windows -static-libgcc -static-libstdc++ 
DEBUG_COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#BUILD_PATH specifies the name of our exectuable
RELEASE_BUILD_PATH = .\release
DEBUG_BUILD_PATH = .\debug

#This is the target that compiles our executable
all: release 

fresh_release: clean_release init_release release

fresh_debug: clean_debug init_debug debug

release: $(SOURCES)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(RELEASE_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_BUILD_PATH)\app

debug: $(SOURCES)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(DEBUG_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_BUILD_PATH)\app

init_release:
	xcopy $(RESOURCE_PATH) $(RELEASE_BUILD_PATH) /i /s /y
	xcopy $(BIN_PATH) $(RELEASE_BUILD_PATH) /i /s /y

init_debug:
	xcopy $(RESOURCE_PATH) $(DEBUG_BUILD_PATH) /i /s /y
	xcopy $(BIN_PATH) $(DEBUG_BUILD_PATH) /i /s /y

clean: clean_release clean_debug

clean_release:
	rd $(RELEASE_BUILD_PATH) /s /q
	md $(RELEASE_BUILD_PATH)

clean_debug:
	rd $(DEBUG_BUILD_PATH) /s /q
	md $(DEBUG_BUILD_PATH)