# Source directories
SRC_DIRS = win win/win32

# Output directory
OUT_DIR = bin

#Executable name
EXECUTABLE = $(OUT_DIR)/deved.exe

# Compiler flags
CFLAGS = -c -Wall -std=c++11 -I"C:\Program Files (x86)\Lua\5.1\include" -I. -DWIN32 -mwindows

# Linker Flags
LDFLAGS = -llua52 -lcomctl32

CC = g++
MD = mkdir
RM = rmdir /S /Q
CP = copy /Y 

# Compute buil dirs (before modify SRC_DIRS)
BUILD_DIRS = $(addprefix $(OUT_DIR)\,$(SRC_DIRS))

# Sources
SRC_DIRS += .
SOURCES = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))

SRCOBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst %,$(OUT_DIR)/%,$(SRCOBJECTS))

# Make
all: directories $(SOURCES) $(EXECUTABLE) $(OUT_DIR)\deved.exe.manifest

# Directories
directories: $(OUT_DIR) $(BUILD_DIRS)

$(OUT_DIR):
	$(MD) $(OUT_DIR)

$(BUILD_DIRS):
	$(MD) $@
	
# Manifest
$(OUT_DIR)\deved.exe.manifest: deved.exe.manifest
	$(CP) deved.exe.manifest $(OUT_DIR)\deved.exe.manifest

# Link
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile
bin/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	$(RM) $(OUT_DIR)\
