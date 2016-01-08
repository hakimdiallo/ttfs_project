CC = gcc
FLAGS = -fPIC	
CFLAGS = -fPIC -Wall
LDFLAGS = -shared
EXEC = tfs_console
TARGET = libll.so
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBNAME = ll
OBJECTS = $(SOURCES:.c=.o)

all: $(OBJECTS)

#lib:	$(TARGET)

lib: $(OBJECTS)
	$(CC) -shared -Wl,-soname,lib$(LIBNAME).so -o $(EXEC) $(CFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

%.o:	%.c $(HEADERS)
	$(CC) -o $@	-c $< $(CFLAGS)
	
clean:
	rm -f $(OBJECTS)
	rm -f *~

mrproper: clean
	rm -f $(EXEC)
