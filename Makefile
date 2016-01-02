CC = gcc
FLAGS = -fPIC	
CFLAGS = -fPIC -Wall
LDFLAGS = -shared
EXECS = tfs_create tfs_partition tfs_analyze
TARGET = libll.so
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBNAME = ll
OBJECTS = $(SOURCES:.c=.o)

all: $(OBJECTS)


tfs_create: tfs_create.o
	$(CC) -o tfs_create tfs_create.c

tfs_partition: tfs_partition.o
	$(CC) -o tfs_partition tfs_partition.c

tfs_analyze:	tfs_analyze.o
	$(CC) -o tfs_analyze tfs_analyze.c

lib:	$(TARGET)

intall: $(EXECS)

$(TARGET): $(OBJECTS)
	$(CC) -shared -Wl,-soname,$(TARGET) -o $(OBJECTS) $(CFLAGS)

%.o:	%.c
	$(CC) -o $@	-c $< $(CFLAGS)
	


clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXECS)
