/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <SFML/Network.hpp>

    #include "./UdpManager.hpp"
    #include "./TcpManager.hpp"
    #include "./Serialization.hpp"
    #include "../Engine.hpp"
    #include "../ClientSession.hpp"

    class Engine;

    class Network {
        public:
            Network(Engine &engine, std::string ip, std::string port);
            ~Network();
            void connectionTcp();
            void connectionUdp();
            void gameProtocol();
            Code &getCode();
            TcpManager &getTcp();
            UdpManager &getUdp();
            std::vector<ClientSession*> &getClient();

            class NetworkException : public std::runtime_error {
                public:
                    NetworkException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            unsigned short _port;
            sf::IpAddress _serverIP;
            Code *_code;
            UdpManager *_udp;
            bool _connectedTcp;
            bool _connectedUdp;
            TcpManager *_tcp;
            Engine *_engine;
            std::vector<ClientSession*> _clients;
    };

#endif /* !NETWORK_HPP_ */
