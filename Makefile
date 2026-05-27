.PHONY: all clean run

### Main build variables

CC = gcc

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = updater

CFLAGS = -Wall -Wextra -O2
CPPFLAGS = -I$(INCLUDE_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET_PATH = $(BIN_DIR)/$(TARGET)

all: $(TARGET_PATH)

### Build cJSON static library

LIB_CJSON_DIR = lib_cJSON
LIB_CJSON_TARGET = libcjson.a

LIB_CJSON_INCLUDE_DIR = $(LIB_CJSON_DIR)/$(INCLUDE_DIR)
LIB_CJSON_SRC_DIR = $(LIB_CJSON_DIR)/$(SRC_DIR)
LIB_CJSON_OBJ_DIR = $(LIB_CJSON_DIR)/$(OBJ_DIR)
LIB_CJSON_BIN_DIR = $(LIB_CJSON_DIR)/$(BIN_DIR)

$(LIB_CJSON_OBJ_DIR)  $(LIB_CJSON_BIN_DIR) : 
	mkdir -p $@

LDFLAGS += -L$(LIB_CJSON_BIN_DIR) -lcjson
CPPFLAGS += -I$(LIB_CJSON_INCLUDE_DIR)
LIB_CJSON_TARGET_PATH = $(LIB_CJSON_BIN_DIR)/$(LIB_CJSON_TARGET)

LIB_CJSON_SRCS = $(wildcard $(LIB_CJSON_SRC_DIR)/*.c)
LIB_CJSON_OBJS = $(LIB_CJSON_SRCS:$(LIB_CJSON_SRC_DIR)/%.c=$(LIB_CJSON_OBJ_DIR)/%.o)

$(LIB_CJSON_OBJ_DIR)/%.o: $(LIB_CJSON_SRC_DIR)/%.c | $(LIB_CJSON_OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LIB_CJSON_INCLUDE_DIR) -c $< -o $@

$(LIB_CJSON_TARGET_PATH): $(LIB_CJSON_OBJS) | $(LIB_CJSON_BIN_DIR)
	ar rcs $@ $^

### Main build rules

$(BIN_DIR) $(OBJ_DIR) : 
	mkdir -p $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET_PATH): $(LIB_CJSON_TARGET_PATH) $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

run: all
	./$(TARGET_PATH)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_CJSON_OBJ_DIR) $(LIB_CJSON_BIN_DIR)
