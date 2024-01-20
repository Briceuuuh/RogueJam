##
## EPITECH PROJECT, 2023
## B-CPP-500-RUN-5-1-rtype-florian.etheve
## File description:
## Makefile
##

SRC		=		src/Package.cpp \
				src/Serialization.cpp \
				src/ClientManager.cpp \
				src/Server.cpp \
				main.cpp

INC		=		-std=c++20 -O3 -I ./include -lsfml-network -lsfml-system

CXXFLAGS+=		$(INC) -W -Werror -Wall -Wextra

NAME	=		rtype_server

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(CXXFLAGS) $(SRC)
	cp $(NAME) ../

clean:
		rm -rdf $(NAME)

fclean:	clean
		rm -rdf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
