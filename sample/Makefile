CC=gcc
BUILD_DIR=../build
LIBPBIT=$(BUILD_DIR)/lib/libpbit.a
CFLAGS=-Wall -c
INC=-I../library/include
OBJ_DIR=$(BUILD_DIR)/obj
OUT_DIR=$(BUILD_DIR)/bin
OUT_FILE_NAME=$(OUT_DIR)/pbit_sample

# Enumerating of every *.c as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard *.c))
	$(CC) $^ $(LIBPBIT) -o $@

#Compiling every *.c to *.o
$(OBJ_DIR)/%.o: %.c dirmake
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<
	
dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

rebuild: clean build
