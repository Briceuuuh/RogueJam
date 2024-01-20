/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Package.hpp
*/

#ifndef PACKAGE_HPP_
    #define PACKAGE_HPP_
    #include "Imports.hpp"

    class IPackage {
        public:
            IPackage() = default;
            virtual void pack() = 0;
            virtual const std::string &getBuffer() const = 0;

            virtual void setPacket(sf::Packet) = 0;
            virtual sf::Packet getPacket() const = 0;

        protected:
        private:
    };

    class Package : public IPackage {
        public:
            Package();

            void pack();
            void setBuffer(const std::string &);
            const std::string &getBuffer() const;

            void setPacket(sf::Packet);
            sf::Packet getPacket() const;

            ~Package();
        protected:
            sf::Packet package;
            std::string buffer;
    };

#endif /* !PACKAGE_HPP_ */
