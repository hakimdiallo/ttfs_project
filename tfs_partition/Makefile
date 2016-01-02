CC = gcc	
CFLAGS = -Wall
EXEC = tfs_partition
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

all: $(EXEC)

$(EXEC):	$(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:	%.c
	$(CC) -o $@	-c $< $(CFLAGS)
	
clean:
	rm -f $(OBJECTS) *~

mrproper: clean
	rm -f $(EXEC)
