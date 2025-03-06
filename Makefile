CC = gcc
CFLAGS = -I"/usr/include/SDL2"
LDFLAGS = -lSDL2
TARGET = rotating_cube
SRC = rotating_cube.c

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
    rm -f $(TARGET)