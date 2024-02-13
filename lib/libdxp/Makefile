LIB_DIR			:= lib
OBJ_DIR			:= obj
INCLUDE_DIR		:= include/dxp
SRC_DIR			:= src

SRC_FILES		:= $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIB_NAME		:= libdxp
CC				:= clang
CFLAGS			=
CPPFLAGS		:= -I$(INCLUDE_DIR)
LDFLAGS			= -lcrypto -lmagic -lssl
DYFLAGS			= -fPIC -shared -undefined dynamic_lookup

LIB_STATIC		:= $(LIB_NAME).a
LIB_SHARED		:=

UNAME			:= $(shell uname)

ifeq ($(UNAME), Darwin)
	LIB_SHARED	:= $(LIB_NAME).dylib
else ifeq ($(UNAME), Linux)
	LIB_SHARED	:= $(LIB_NAME).so
else
	$(error Unsupported OS: $(UNAME))
endif

TARGET_FILES	:= $(LIB_DIR)/$(LIB_STATIC) $(LIB_DIR)/$(LIB_SHARED)

.PHONY: clean all .FORCE
all: clean $(TARGET_FILES)

$(TARGET_FILES): $(OBJ_FILES) | $(LIB_DIR)

$(LIB_DIR)/%.a: $(OBJ_FILES)
	ar rcs $@ $^

$(LIB_DIR)/%.dylib: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DYFLAGS) -o $@ $^

$(LIB_DIR)/%.so: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DYFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $<

$(LIB_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	$(RM) -rf $(LIB_DIR) $(OBJ_DIR)
