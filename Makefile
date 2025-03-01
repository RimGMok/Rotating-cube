CC = gcc
CFLAGS = -I"C:\mingw64\x86_64-w64-mingw32\include"
LDFLAGS = -L"C:\mingw64\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2

TARGET = rotating_cube.exe
SRC = rotating_cube.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
