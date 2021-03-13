# HEADERS
HEAD = 
# C FILES
C = defs.h draw.c init.c input.c main.c structs.h
#What compiler are you using?
CC = gcc
#What compiler flags are you using?
COMPILER_FLAGS = -lm
#What libraries are you linking?
LINKER_FLAGS = -lSDL2 -lSDL2_image
#What's the name of the executable?
OBJ_NAME = test

all: $(OBJS)
	$(CC) $(C) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
