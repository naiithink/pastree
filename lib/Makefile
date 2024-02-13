OBJ_DIR			:= obj
LIB_DIR			:= lib

LIBS			:= $(shell find . -type d -regex "\./$(LIB_DIR)..*" -maxdepth 1 | sed -ne 's/\.\/\(.*\)/\1/p')

.PHONY: clean all libs pack .FORCE
all: pack

pack: libs
	@rsync -rp $(LIBS)/$(LIB_DIR)/* $(LIB_DIR)
	@rsync -rp $(LIBS)/$(OBJ_DIR)/* $(OBJ_DIR)

libs:
	$(MAKE) -C $(LIBS) CC?=$(CC) CFLAGS+="$(CFLAGS)" CPPFLAGS+="$(CPPFLAGS)" LDFLAGS+="$(LDFLAGS)"

clean:
	$(MAKE) -C $(LIBS) clean
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(LIB_DIR)
