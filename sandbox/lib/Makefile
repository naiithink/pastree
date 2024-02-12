BIN			:= test

CC			:= clang
CFLAGS		:= -I../../include
CPPFLAGS	:= -L../../lib
LDFLAGS		:= -ldxp

TARGET		:= $(BIN)

.PHONY: clean all .FORCE
all: clean $(TARGET)

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $@

clean:
	$(RM) -rf $(TARGET)
