TARGET = def
CFLAGS =  -std=c99 `pkg-config --cflags glib-2.0`
LDFLAGS =  `pkg-config --libs glib-2.0` -lswni
CC = gcc
LD = $(CC)

all: $(TARGET)

def.o: def.c
	$(CC) $(CFLAGS) -c def.c -o def.o

$(TARGET): def.o
	$(LD) def.o -o def $(LDFLAGS)
clean:
	rm def def.o
.PHONY: all clean
