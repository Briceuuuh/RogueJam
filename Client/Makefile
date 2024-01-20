##
## EPITECH PROJECT, 2023
## Projet_B (rtype-client)
## File description:
## Makefile
##

ENGINE_DIR = ../Engine

MAIN = main.cpp \
		Game/Game.cpp

INC_CLIENT = -Iinclude
CPPFLAGS_CLIENT = $(INC_CLIENT) -W -Werror -Wall -Wextra -std=c++20

LDFLAGS_CLIENT = -L$(ENGINE_DIR) -lEngine -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-network

OBJ_CLIENT = $(MAIN:.cpp=.o)
NAME_CLIENT = rtype_client

all: $(NAME_CLIENT)

$(NAME_CLIENT):	$(OBJ_CLIENT)
	g++ -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS_CLIENT)

%.o: %.cpp
	g++ $(CPPFLAGS_CLIENT) -c -o $@ $<

clean:
	rm -rdf $(OBJ_CLIENT)

fclean: clean
	rm -rdf $(NAME_CLIENT)

re: fclean all
