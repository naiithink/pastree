CC				:= clang
CFLAGS			:= -I../include
CPPFLAGS		:= -L../lib
LDFLAGS			:= -ldxp

LIB_DIR			:= lib
TARGET			:=

.PHONY: clean all libs .FORCE
all: clean libs $(TARGET)

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $@

libs:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) -rf $(TARGET)
