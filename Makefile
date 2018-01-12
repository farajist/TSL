#OBJS : file to compile as part of the project
OBJS = json/json_writer.cpp json/class_descriptor.cpp json/json.cpp foo.cpp main.cpp

#CC compiler to be used
CC = g++

#INCLUDE_PATHS : addtional include paths needed
# INCLUDE_PATHS = `sdl2-config --cflags`

#LIBRARY_PATHS : addtional library paths needed
# LIBRARY_PATHS = `sdl2-config --libs`


#COMPILER_FLAGS
COMPILER_FLAGS = -Wall --std=c++14

#LINKER_FLAGS : libraries we're linking against
# LINKER_FLAGS = -lSDL2_image

#OBJ_NAME : executable name
OBJ_NAME = jsonpp

#Target that compiles the executable

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)