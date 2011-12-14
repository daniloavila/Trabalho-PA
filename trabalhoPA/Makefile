CC=gcc
CFLAGS=-c -std=c99 -lm
LDFLAGS=  -lm
SOURCES=src/Main.c src/StringsUtil.c src/Arquivo.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=programa

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -lm -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean: 
	rm $(OBJECTS) $(EXECUTABLE)  