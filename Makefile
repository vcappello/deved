# Sources
SOURCES = deved.cpp

# Output directory
OUT_DIR = bin

#Executable name
EXECUTABLE = $(OUT_DIR)/deved.exe

# Compiler flags
CFLAGS = -c -Wall -std=c++11 -I"C:\Program Files (x86)\Lua\5.1\include" -I.

# Linker Flags
LDFLAGS = -L"C:\Program Files (x86)\Lua\5.1\lib" -llua5.1

CC = g++
MD = mkdir
RM = del /Q

SRCOBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst %,$(OUT_DIR)/%,$(SRCOBJECTS))

# Make
all: directories $(SOURCES) $(EXECUTABLE)

# Directories
directories: $(OUT_DIR)

$(OUT_DIR):
	$(MD) $(OUT_DIR)

# Link
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile
bin/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	$(RM) $(OUT_DIR)
