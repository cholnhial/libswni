TARGET = libswni.so
OBJECTS = src/swni.o src/wni.o
CFLAGS = -fPIC -g -c -Wall -std=c99 -I include/ `pkg-config --cflags glib-2.0`
LDFLAGS = -shared -fPIC `pkg-config --cflags --libs glib-2.0` -lwordnet 

CC = gcc
LD = $(CC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm $(TARGET) src/*.o


install: $(TARGET)
	cp $(TARGET) /usr/lib
	cp -r include/swni /usr/include

uninstall: $(TARGET)
	rm /usr/lib64/$(TARGET)
	rm -r /usr/include/swni

.PHONY: all clean install uninstall

