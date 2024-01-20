/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_
    #include "ClientManager.hpp"
    #include "Serialization.hpp"
    #include <fstream>

    class Server {
        public:
            Server();
            Server(const std::string &/*port*/);

            void run();

            void addClient(size_t);
            void onLineTcp();
            void actionTcp(ClientManager *);

            void onLineUdp();
            bool injectReady(ClientManager *);
            bool sendToAllUdp(std::string, size_t);

            ~Server();

        protected:
            enum STATE {
                Waiting,
                Ready,
                Launched
            };
            STATE state;
            sf::TcpListener listener;
            sf::SocketSelector selector;
            std::vector<ClientManager *> clients;
            std::vector<std::string> saveUdp;
            size_t clients_ready;
            sf::UdpSocket *udp;
            Code *code;
            bool running;
            std::ofstream LogFile;
            std::bitset<4> identifier;
            std::hash<std::bitset<4>> hash_id;
        private:
    };

#endif /* !SERVER_HPP_ */
