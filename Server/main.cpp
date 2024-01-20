/*
** EPITECH PROJECT, 2023
** CPP
** File description:
** main_server
*/
#include "./include/Server.hpp"

int main(int ac, char **av)
{
    bool help = false;
    for (uint8_t i = 0; av[i] != NULL; i++) {
        if (std::strcmp(av[i], "-h") == 0) {
            std::cout << "R-TYPE SERVER:\n\t\tContext:\n\t\t\tThis binairy launches the server of our R-TYPE like game. You can connect multiple clients with it.\n\t\t\tThis server has many rooms that you can play with. Enjoy !\n\n\t\tUsage:\trtype_server [port] [-h]:\n\t\t\t\t\t[port] => Choose the number of the port you want to launch the port with.\n\t\t\t\t\t[-h] => The manual of the usage" << std::endl;
            help = true;
        }
    }
    if (ac < 2)
        Server();
    else if (help == false)
        Server server(av[1]);
    return (0);
}
