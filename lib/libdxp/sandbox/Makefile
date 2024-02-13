CC				:= clang
CFLAGS			:= -g -Og
CPPFLAGS		:= -I../include
LDFLAGS			:= -L../lib -ldxp

.PHONY: clean all .FORCE
all: clean libs $(TARGET)

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) -rf $(TARGET)
