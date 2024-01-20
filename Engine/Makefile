##
## EPITECH PROJECT, 2023
## B-CPP-500-RUN-5-1-rtype-florian.etheve
## File description:
## Makefile
##

COMP = GameEngine/Component/Damage/Damage.cpp \
    GameEngine/Component/Health/Health.cpp \
    GameEngine/Component/Hitbox/Hitbox.cpp \
    GameEngine/Component/IA/IA.cpp \
    GameEngine/Component/ID/ID.cpp \
    GameEngine/Component/Mobility/Mobility.cpp \
    GameEngine/Component/Player/Player.cpp \
    GameEngine/Component/Position/Position.cpp \
    GameEngine/Component/Text/Text.cpp \
    GameEngine/Component/Visual/Visual.cpp \
    GameEngine/Component/Invalid/Invalid.cpp

ENGINE = GameEngine/Engine/Engine.cpp \
    GameEngine/Engine/Window.cpp \
    GameEngine/Engine/ClientSession.cpp

NETWORK = GameEngine/Engine/Network/Network.cpp \
    GameEngine/Engine/Network/TcpManager.cpp \
    GameEngine/Engine/Network/UdpManager.cpp \
    GameEngine/Engine/Network/Serialization.cpp

MANAGERS = GameEngine/Engine/EManagers/EntityManager.cpp \
    GameEngine/Engine/EManagers/EventManager.cpp \
    GameEngine/Engine/EManagers/WindowManager.cpp \
    GameEngine/Engine/EManagers/SceneManager.cpp \
    GameEngine/Engine/EManagers/SoundManager.cpp \
    GameEngine/Engine/EManagers/SystemManager.cpp

ENTITY = GameEngine/Entity/Entity.cpp

SYSTEM = GameEngine/System/System.cpp \
        GameEngine/System/Clock.cpp

SCENE = GameEngine/Scene/Scene.cpp

ENGINESRC = $(COMP) \
    $(ENGINE) \
    $(ENTITY) \
    $(SCENE) \
    $(NETWORK) \
    $(SYSTEM) \
    $(MANAGERS)

INC_ENGINE = -Iinclude
CPPFLAGS_ENGINE = $(INC_ENGINE) -W -Werror -Wall -Wextra -std=c++20

OBJ_ENGINE = $(ENGINESRC:.cpp=.o)
LIB_ENGINE = libEngine.a

all: $(LIB_ENGINE)

$(LIB_ENGINE): $(OBJ_ENGINE)
		ar rcs $(LIB_ENGINE) $(OBJ_ENGINE)

%.o: %.cpp
		g++ $(CPPFLAGS_ENGINE) -c -o $@ $<

clean:
		rm -rdf $(OBJ_ENGINE)

fclean: clean
		rm -rdf $(LIB_ENGINE)

re: fclean all
