NAME			:= libdxp_static
CC				:= clang
CFLAGS			:= -lmagic
LIBSOURCE_DIR	= lib
BUILD_DIR		= build
TEST_DIR		= tests
LIB_OUT			:= libdxp_static.a libdxp_shared.so

.PHONY: all clean test .FORCE

all: clean $(LIB_OUT)

%.a: %.o
	ar r $(LIBSOURCE_DIR)/$@ $(LIBSOURCE_DIR)/$<

%.so: %.o
	$(CC) $(CFLAGS) -shared -o $(LIBSOURCE_DIR)/$@ $(LIBSOURCE_DIR)/$<

%.o: %.c
	$(CC) $(CFLAGS) -c -fPIC -o $(BUILD_DIR)/$@ $(LIBSOURCE_DIR)/$<

clean:
	$(RM) -rf build/libdxp*.a \
		build/libdxp*.so \
		build/libdxp*.dSYM
