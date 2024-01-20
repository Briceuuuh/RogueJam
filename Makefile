##
## EPITECH PROJECT, 2023
## B-CPP-500-RUN-5-1-rtype-florian.etheve
## File description:
## Makefile
##

SERVER_NAME = rtype_server

CLIENT_NAME = rtype_client

all:
	make -j -C ./Engine/ all
	make -j -C ./Server/ all
	make -j -C ./Client/ all
	mv ./Client/$(CLIENT_NAME) .
	mv ./Server/$(SERVER_NAME) .

clean:
	make -j -C ./Engine/ clean
	make -j -C ./Server/ clean
	make -j -C ./Client/ clean

fclean: clean
	make -j -C ./Engine/ fclean
	make -j -C ./Server/ fclean
	make -j -C ./Client/ fclean
	rm -rdf $(SERVER_NAME)
	rm -rdf $(CLIENT_NAME)

re: fclean all
