/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ClientManager.hpp
*/

#ifndef CLIENTMANAGER_HPP_
    #define CLIENTMANAGER_HPP_
    #include "Transmission.hpp"

    class  ClientManager {
        public:
            ClientManager(size_t id);

            void setConnect(bool);
            bool getConnect() const;

            size_t getId() const;

            void setFirst();
            bool getFirst() const;

            void onListenTcp();
            void onListenUdp();

            Transmission<sf::TcpSocket> *getTcp() const;

            void setIp(sf::IpAddress);
            sf::IpAddress getIp() const;

            void setPort(unsigned short);
            unsigned short getPort() const;

            bool addInfo(sf::IpAddress, unsigned short, size_t);

            ~ClientManager();

        protected:
            size_t id;
            Transmission<sf::TcpSocket> *tcp;
            sf::IpAddress ip;
            unsigned port;
            bool first;
            bool connected;
        private:
    };

#endif /* !CLIENTMANAGER_HPP_ */
