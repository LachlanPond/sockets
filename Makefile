# Linux setup
INC_DIR = -Iinc -Ilinux/inc
DEPS = linux/socketfunc.c
CC = gcc
CFLAGS = -Wall

# Windows setup
WIN_INC_DIR = -Iinc -Iwinblows/inc
WIN_DEPS = winblows/socketfunc.c
WIN_CC = x86_64-w64-mingw32-gcc
WIN_CFLAGS = -lwsock32

make:
	$(CC) client.c $(DEPS) -o linux/client $(INC_DIR)
	$(CC) linux/server.c -o linux/server $(INC_DIR)

windows:
	$(WIN_CC) client.c $(WIN_DEPS) -o winblows/client64.exe $(WIN_INC_DIR) $(WIN_CFLAGS)