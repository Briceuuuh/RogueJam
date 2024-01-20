/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** UdpManager.hpp
*/

#ifndef UDPMANAGER_HPP_
    #define UDPMANAGER_HPP_
    #include <SFML/Network.hpp>
    #include <iostream>

    class UdpManager {
        public:
            UdpManager(const std::string &, const std::string &);
            sf::UdpSocket &getSocket() const;
            void sendPackage(std::string string);
            void receivePackage();
            void setPackage(const std::string &);
            void sendPackage();
            void addPackage(const std::string &, uint16_t);
            sf::Packet &getSendedPackage();
            std::string &getReceivedString();
            sf::Packet &getPackage() const;

            class UdpException : public std::runtime_error {
                public:
                    UdpException(const std::string& msg) : std::runtime_error(msg) {};
            };
            ~UdpManager();
        private:
            sf::UdpSocket *_socket;
            sf::IpAddress _serverIP;
            unsigned short _serverPort;
            sf::Packet *_sendedPacket;
            std::string _receivedPacket;
    };

#endif /* !UDPMANAGER_HPP_ */
