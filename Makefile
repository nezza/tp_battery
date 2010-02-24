#Thomas Roth, 24.02.2010

#Compiler:
CC = gcc

#Comiler Flags:
CFLAGS += -Wall -g -std=c99

#Linker Flags:
LDFLAGS += -lm

#Source Files:
SOURCES += tp_battery.c
OBJECTS = $(SOURCES:.cpp=.o)

#Executable name:
EXECUTABLE = tp_battery

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) -g $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
