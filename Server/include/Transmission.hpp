/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Transmission.hpp
*/

#ifndef TRANSMISSION_HPP_
    #define TRANSMISSION_HPP_

    #include "Package.hpp"

    template <typename T>
    class Transmission {
        public:
            Transmission() {
                this->socket = new T();
                this->package = new Package();
            };

            void read() {
                sf::Packet packet = this->package->getPacket();
                if (dynamic_cast<T *>(this->socket)->receive(packet) == sf::Socket::Done) {
                    this->package->setPacket(packet);
                    this->package->pack();
                } else {
                    std::cout << "error read" << std::endl;
                }
            };

            void send(const std::string &str) {
                if (dynamic_cast<T *>(this->socket)->send(str.c_str(), str.size()) == sf::Socket::Done) {
                    std::cout << "resultat de l'envoi : " << str << std::endl;
                } else {
                    std::cout << "error read" << std::endl;
                }
            };

            T *getSocket() const {
                return static_cast<T *>(this->socket);
            };

            Package *getPack() const {
                return this->package;
            }

            ~Transmission() {
                delete socket;
            };

        protected:
            sf::Socket *socket;
            Package *package;
        private:
    };

#endif /* !TRANSMISSION_HPP_ */
