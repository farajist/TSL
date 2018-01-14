#CC compiler to be used
CC = g++

#COMPILER_FLAGS
COMPILER_FLAGS = -Wall -std=c++17

#Executable 
jsonpp : main.o foo.o json.o \
		class_descriptor.o map_type_descriptor.o array_type_descriptor.o \
		vector_type_descriptor.o json_writer.o json_reader.o json_lexer.o
		$(CC) -o jsonpp main.o foo.o json.o \
				class_descriptor.o map_type_descriptor.o array_type_descriptor.o \
				vector_type_descriptor.o json_writer.o json_reader.o json_lexer.o
		rm  main.o foo.o json.o \
				class_descriptor.o map_type_descriptor.o array_type_descriptor.o \
				vector_type_descriptor.o json_writer.o json_reader.o json_lexer.o

#OBJS : file to compile as part of the project

main.o : main.cpp
	$(CC) $(COMPILER_FLAGS) -c main.cpp 

foo.o : foo.cpp
	$(CC) $(COMPILER_FLAGS) -c foo.cpp 

json.o : json/json.cpp json/json_writer.h json/json_reader.h json/class_descriptor.h \
		json/array_type_descriptor.h json/map_type_descriptor.h json/vector_type_descriptor.h
	$(CC) $(COMPILER_FLAGS) -c json/json.cpp 

class_descriptor.o : json/class_descriptor.cpp
	$(CC) $(COMPILER_FLAGS) -c json/class_descriptor.cpp 

map_type_descriptor.o : json/map_type_descriptor.cpp
	$(CC) $(COMPILER_FLAGS) -c json/map_type_descriptor.cpp 

array_type_descriptor.o : json/array_type_descriptor.cpp
	$(CC) $(COMPILER_FLAGS) -c json/array_type_descriptor.cpp 

vector_type_descriptor.o : json/vector_type_descriptor.cpp json/array_type_descriptor.h
	$(CC) $(COMPILER_FLAGS) -c json/vector_type_descriptor.cpp 

json_writer.o : json/json_writer.cpp
	$(CC) $(COMPILER_FLAGS) -c json/json_writer.cpp 

json_reader.o : json/json_reader.cpp json/json_lexer.h
	$(CC) $(COMPILER_FLAGS) -c json/json_reader.cpp 

json_lexer.o : json/json_lexer.cpp
	$(CC) $(COMPILER_FLAGS) -c json/json_lexer.cpp 



clean :
	rm jsonpp main.o foo.o json.o \
				  class_descriptor.o map_type_descriptor.o array_type_descriptor.o \
				  vector_type_descriptor.o json_writer.o json_reader.o json_lexer.o

