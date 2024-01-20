/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** UdpManager.hpp
*/

#ifndef TCPMANAGER_HPP_
    #define TCPMANAGER_HPP_
    #include <SFML/Network.hpp>
    #include <iostream>

    class TcpManager {
        public:
            TcpManager(const std::string &, const std::string &);
            sf::TcpSocket &getSocket() const;
            void setPackage(const std::string &);
            void addPackage(const std::string &, uint16_t );

            std::string &getReceivedPackage();
            std::string &getSendedPackage();

            void sendPackage(std::string string);
            void sendPackage();
            void receivePackage();

            class TcpException : public std::runtime_error {
                public:
                    TcpException(const std::string& msg) : std::runtime_error(msg) {};
            };

            ~TcpManager();
        private:
            sf::TcpSocket *socket;
            sf::IpAddress serverIP;
            unsigned short serverPort;
            std::string _receivedPacket;
            std::string _sendedPacket;
    };

#endif /* !TCPMANAGER_HPP_ */
