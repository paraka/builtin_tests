#  Makefile for PBIT static library. 

CC=gcc
OUT_FILE_NAME=libpbit.a
CFLAGS=-fPIC -O2 -g -Wall -c
INC=-Iinclude
BUILD_DIR=../build
OBJ_DIR=$(BUILD_DIR)/obj
OUT_DIR=$(BUILD_DIR)/lib

# Enumerating of every *.c as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/*.c))
	ar -r -o $(OUT_DIR)/$@ $^

#Compiling every *.c to *.o
$(OBJ_DIR)/%.o: src/%.c dirmake
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<
	
dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build
