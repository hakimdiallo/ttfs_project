CC = gcc
CFLAGS = -Wall
LDFLAGS = -shared -fPIC
EXECS = tfs_create tfs_partition tfs_analyze
TARGET = libll.so
SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

tfs_create: tfs_create.o
	$(CC) -o tfs_create tfs_create.c

tfs_partition: tfs_partition.o
	$(CC) -o tfs_partition tfs_partition.c

tfs_analyze:	tfs_analyze.o
	$(CC) -o tfs_analyze tfs_analyze.c

#$(EXECS): $(OBJECTS)
#	$(CC) -o $@ $^

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<
	


clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXECS)
