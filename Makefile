SRC_DIR = src
BUILD_DIR = build
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/**/*.cpp)
OBJ_NAME = begemmed.exe
TARGET = $(BUILD_DIR)/$(OBJ_NAME)
COMPILER_FLAGS = -fdiagnostics-color=always -std=c++20 -Wall -Wextra -O0 -g -Dmain=SDL_main
INCLUDE_PATHS = -Iinclude -I. -IC:/msys64/ucrt64/include -IC:/msys64/ucrt64/include/SDL2
LINKED_FLAGS = -L C:/msys64/ucrt64/lib -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#-lmodplug -lfontconfig -lfribidi
.PHONY: all clean
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	@mkdir -p $(BUILD_DIR) # Ensure the build directory exists recursively
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(SRC_FILES) $(LINKED_FLAGS) -o $@
	@echo "Build successful: $(TARGET)"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR) # Remove the build directory and its contents