SOURCES=bush.c
EXECUTABLE=bush
PREFIX=/usr/local
CFLAGS += -O2

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) $(DESTDIR)$(PREFIX)/bin
