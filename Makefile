CC = gcc
FLAGS = -fPIC	
CFLAGS = -Wall
LDFLAGS = -shared
EXEC = tfs_console
TARGET = libll.so
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBNAME = ll
OBJECTS = $(SOURCES:.c=.o)

all: $(EXEC)

lib: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared $(FLAGS) $(OBJECTS) -o $(TARGET)
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	
update-lib: $(OBJECTS)
	$(CC) -shared -Wl,-soname,lib$(LIBNAME).so -o $(EXEC) $(CFLAGS)

$(EXEC): $(TARGET)
	$(CC) -o $@ $^

%.o:	%.c $(HEADERS)
	$(CC) -o $@	-c $(FLAGS) $< $(CFLAGS)
	
clean:
	rm -f $(OBJECTS)
	rm -f *~

mrproper: clean
	rm -f $(EXEC) 
	rm -f $(TARGET)
