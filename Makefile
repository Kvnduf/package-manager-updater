.PHONY: all clean run


CC = gcc

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin


$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

TARGET = updater

CFLAGS = -Wall -Wextra -O2
CPPFLAGS = -I$(INCLUDE_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET_PATH = $(BIN_DIR)/$(TARGET)


all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run: all
	./$(TARGET_PATH)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
