all: sock_server sock_client 
CC := gcc
LINKFLAGS = rt

.PHONY: all

sock_server: sock_server.o
	@$(CC) -o server sock_server.o 
	@echo Client Build Complete

sock_client: sock_client.o
	@$(CC) -o client sock_client.o
	@echo Server build Complete

%.o:%.c
	@$(CC) -c $< 

.PHONY: clean
clean:
	@rm  ./*.o
	@rm  ./server
	@rm  ./client
	@echo clean complete
