CC = gcc
CFLAGS = -I"/usr/include/SDL2" -Dmain=SDL_main
LDFLAGS = -lmingw32 -lSDL2main -lSDL2
TARGET = rotating_cube.exe
SRC = rotating_cube.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)