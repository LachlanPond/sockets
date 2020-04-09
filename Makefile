make:
	gcc linux/client.c -o linux/client
	gcc linux/server.c -o linux/server

windows:
	x86_64-w64-mingw32-gcc winblows/client.c -o winblows/client64.exe -lwsock32