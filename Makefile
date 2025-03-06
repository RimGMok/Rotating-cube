CC = gcc
CFLAGS = -I"/usr/include/SDL2"
LDFLAGS = -lSDL2main -lSDL2
TARGET = rotating_cube.exe
SRC = rotating_cube.c

# Detect platform
ifeq ($(OS),Windows_NT)
    CFLAGS += -Dmain=SDL_main
    LDFLAGS += -lmingw32 -lSDL2main -lSDL2 -mwindows
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)