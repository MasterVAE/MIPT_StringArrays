SOURCES = main.cpp sorting.cpp array.cpp

OBJ_DIR = obj
SOURCE_DIR = .

OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))

TARGET = a.out

CC = g++
CFLAGS =-O3
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Linked Successfully"

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled Successfully $<"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned Successfully"
