SOURCES = main.cpp code/sorting.cpp code/array.cpp

OBJ_DIR = obj
SOURCE_DIR = .

OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = Onegin.out

CC = g++
CFLAGS = -O3

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Linked Successfully"
	@rm -rf $(OBJ_DIR)
	@echo "Removed object directory after build."

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled Successfully $<"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned Successfully"
