BIN_DIR			:= bin
SRC_DIR			:= src
INCLUDE_DIR		:= include
LIB_DIR			:= lib

CC				:= clang
CFLAGS			:= -O2
CPPFLAGS		:= -I$(INCLUDE_DIR)
LDFLAGS			:= -L$(LIB_DIR) -ldxp

.PHONY: all bin clean libs .FORCE
all: clean libs bin

bin:

libs:
	$(MAKE) -C $(LIB_DIR) CC?=$(CC) CFLAGS+="$(CFLAGS)" CPPFLAGS+="$(CPPFLAGS)" LDFLAGS+="$(LDFLAGS)"

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) -rf $(BIN_DIR)
