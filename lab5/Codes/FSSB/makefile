CC = g++
CFLAGS = -c -Wall -std=c99
LDFLAGS =
SOURCES := main.cpp FSSB.cpp
OBJECTS = $(SOURCES:.cpp=.o)
BINDIR = bin
EXECUTABLE = $(BINDIR)/FSSB
#-------------------------------------------------------------------------------
ifdef DEBUG
	CFLAGS += -DDEBUG=1
endif
#-------------------------------------------------------------------------------

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	-mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#-------------------------------------------------------------------------------

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -r $(BINDIR)
